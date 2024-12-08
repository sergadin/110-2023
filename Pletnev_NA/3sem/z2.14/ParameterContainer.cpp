#include "ParameterContainer.h"

ParameterValue parseValue(const std::string& valueStr);

// Реализация функции загрузки параметров из файла
void ParameterContainer::loadFromFile(const std::string& filename) 
{
    std::ifstream file(filename);

    if (!file.is_open()) 
    {
        throw Error(-201, "Не удалось открыть файл: " + filename);
    }

    size_t lineNumber = 1;
    std::string line;

    while (std::getline(file, line)) 
    {
        try 
        {
            line = trim(line); //remove leading/trailing whitespaces
            if (line.empty() || line[0] == '#') continue; // Skip empty lines and comments

            size_t eqPos = line.find('=');
            if (eqPos == std::string::npos || eqPos == 0 || eqPos == line.length() - 1) 
            {
                throw Error(-202, "Неверный формат строки (ожидается '='): строка " + std::to_string(lineNumber) + ": " + line);
            }

            std::string key = trim(line.substr(0, eqPos));
            std::string valueStr = trim(line.substr(eqPos + 1));

            if (key.empty()) 
            {
                throw Error(-203, "Пустой ключ: строка " + std::to_string(lineNumber) + ": " + line);
            }

            //Improved error handling:
            insert(key, parseValue(valueStr));

        } catch (const Error& e) {
            std::cerr << "Ошибка в строке " << lineNumber << ": " << e.what() << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Неверный аргумент в строке " << lineNumber << ": " << e.what() << std::endl;
            throw Error(-204, "Неверный формат числа: строка " + std::to_string(lineNumber) + ": " + line);
        } catch (const std::out_of_range& e) {
            std::cerr << "Число вне диапазона в строке " << lineNumber << ": " << e.what() << std::endl;
            throw Error(-205, "Число слишком большое или слишком маленькое: строка " + std::to_string(lineNumber) + ": " + line);
        } catch (const std::exception& e) {
            std::cerr << "Неожиданная ошибка в строке " << lineNumber << ": " << e.what() << std::endl;
            throw Error(-206, "Неизвестная ошибка: строка " + std::to_string(lineNumber) + ": " + line);
        }

        lineNumber++;
    }
}

// Реализация функции обрезки пробелов
std::string ParameterContainer::trim(const std::string& str) const 
{
    std::string s = str;
    s.erase(std::remove_if(s.begin(), s.end(), [](char c){ return std::isspace(c); }), s.end());
    return s;
}

// Функция для разбора строки в значение параметра
ParameterValue parseValue(const std::string& valueStr) 
{
    ParameterValue result; // Создаем объект для результата

    // Проверяем, является ли строка массивом (начинается с '[' и заканчивается ']')
    if (valueStr[0] == '[' && valueStr.back() == ']') 
    {
        std::string innerStr = valueStr.substr(1, valueStr.length() - 2); // Извлекаем внутреннюю часть строки (без скобок)
        bool hasDecimal = std::any_of(innerStr.begin(), innerStr.end(), [](char c){ return c == '.'; }); // Проверяем наличие десятичной точки

        // Разные лямбда-функции для разбора массивов целых и вещественных чисел
        auto parseDoubleArray = [&]() -> std::optional<std::vector<double>> 
        {
            std::vector<double> arr;
            std::stringstream ss(innerStr);
            double num;
            char comma;

            while (ss >> num) 
            {
                arr.push_back(num);
                if (!(ss >> comma) || comma != ',') 
                {
                  break; //Дошли до конца строки
                }
            }
            if (ss.fail() && !ss.eof()) 
            {
              return std::nullopt; //Ошибка чтения
            }
            return arr;
        };

        auto parseIntArray = [&]() -> std::optional<std::vector<int>> 
        {
            std::vector<int> arr;
            std::stringstream ss(innerStr);
            int num;
            char comma;

            while (ss >> num) 
            {
                arr.push_back(num);
                if (!(ss >> comma) || comma != ',') 
                {
                  break; //Дошли до конца строки
                }
            }
            if (ss.fail() && !ss.eof()) 
            {
              return std::nullopt; //Ошибка чтения
            }
            return arr;
        };

        // Выбираем функцию разбора в зависимости от наличия десятичной точки
        if (hasDecimal) 
        {
            auto parsedArray = parseDoubleArray();
            if (parsedArray.has_value()) 
            {
                result.value = *parsedArray;
                result.type = ParameterValue::Type::DOUBLE_ARRAY;
            } else {
                throw std::runtime_error("Ошибка разбора массива вещественных чисел: " + valueStr);
            }
        } else {

            auto parsedArray = parseIntArray();

            if (parsedArray.has_value()) 
            {
                result.value = *parsedArray;
                result.type = ParameterValue::Type::INT_ARRAY;
            } else {
                throw std::runtime_error("Ошибка разбора массива целых чисел: " + valueStr);
            }
        }
        
    } else { // Разбор одиночного значения

        try 
        {
            result.value = std::stoi(valueStr);
            result.type = ParameterValue::Type::INT;
            
        } catch (const std::invalid_argument& e) {}

        try  
        {
            result.value = std::stod(valueStr);
            result.type = ParameterValue::Type::DOUBLE;
        }  catch (const std::invalid_argument& e) {}

        try
        {
            result.value = valueStr;
            result.type = ParameterValue::Type::STRING;
        } catch (const std::invalid_argument& e) {}       
    }

    return result;
}

std::vector<int> ParameterContainer::parseIntArray(const std::string& valueStr) const 
{
    std::vector<int> arr;
    std::string currentNum;

    for (char c : valueStr) 
    {
        if (isdigit(c) || c == '-') 
        { // Проверяем только цифры и знак минуса
            currentNum += c;
        } else if (c == ',') {

            if (!currentNum.empty()) 
            {
                try 
                {
                    arr.push_back(std::stoi(currentNum));
                    currentNum.clear();
                } catch (const std::invalid_argument& e) {
                    throw Error(-301, "parseIntArray: Недопустимое целочисленное значение в массиве");
                } catch (const std::out_of_range& e) {
                    throw Error(-302, "parseIntArray: Целочисленное значение вне диапазона в массиве");
                }
            }
        } // Другие символы игнорируются
    }

    // Обработка последнего числа
    if (!currentNum.empty()) 
    {
        try 
        {
            arr.push_back(std::stoi(currentNum));
        } catch (const std::invalid_argument& e) {
            throw Error(-301, "parseIntArray: Недопустимое целочисленное значение в массиве");
        } catch (const std::out_of_range& e) {
            throw Error(-302, "parseIntArray: Целочисленное значение вне диапазона в массиве");
        }
    }

    return arr;
}

std::vector<double> ParameterContainer::parseDoubleArray(const std::string& valueStr) const 
{
    std::vector<double> arr;
    std::string currentNum;

    for (char c : valueStr) 
    {
        if (isdigit(c) || c == '.' || c == '-') 
        {
            currentNum += c;
        } else if (c == ',') {
            if (!currentNum.empty()) {
                try {
                    arr.push_back(std::stod(currentNum));
                    currentNum.clear();
                } catch (const std::invalid_argument& e) {
                    throw Error(-303, "parseDoubleArray: недопустимое вещественное значение в массиве");
                } catch (const std::out_of_range& e) {
                    throw Error(-304, "parseDoubleArray: вещественное значение вне диапазона в массиве");
                }
            }
        }
        // Игнорируем другие символы
    }
    // Обработка последнего числа
    if (!currentNum.empty()) 
    {
        try 
        {
            arr.push_back(std::stod(currentNum));
        } catch (const std::invalid_argument& e) {
            throw Error(-303, "parseDoubleArray: недопустимое вещественное значение в массиве");
        } catch (const std::out_of_range& e) {
            throw Error(-304, "parseDoubleArray: вещественное значение вне диапазона в массиве");
        }
    }
    return arr;
}

Node* ParameterContainer::findNode(Node* node, const std::string& key) const 
{
    if (!node) return nullptr; // Базовый случай: узел не найден
    if (key == node->key) return node; // Базовый случай: ключ найден
    if (key < node->key) return findNode(node->left.get(), key); // Рекурсивный вызов для левого поддерева
    return findNode(node->right.get(), key); // Рекурсивный вызов для правого поддерева
}

int ParameterContainer::GetInt(const std::string& key) const 
{
    Node* node = findNode(root_.get(), key);

    if (!node || node->value.type != ParameterValue::Type::INT) 
    {
        throw Error(-110,"GetInt: ключ не найден или неверный тип: " + key);
    }

    return std::get<int>(node->value.value);
}

double ParameterContainer::GetDouble(const std::string& key) const 
{
    Node* node = findNode(root_.get(), key);

    if (!node || node->value.type != ParameterValue::Type::DOUBLE) 
    {
        throw Error(-111,"GetDouble: ключ не найден или неверный тип: " + key);
    }

    return std::get<double>(node->value.value);
}

const std::vector<int>& ParameterContainer::GetIntArray(const std::string& key) const 
{
    Node* node = findNode(root_.get(), key);

    if (!node || node->value.type != ParameterValue::Type::INT_ARRAY) 
    {
        throw Error(-112,"GetIntArray: ключ не найден или неверный тип: " + key);
    }

    return std::get<std::vector<int>>(node->value.value);
}

const std::vector<double>& ParameterContainer::GetDoubleArray(const std::string& key) const 
{
    Node* node = findNode(root_.get(), key);

    if (!node || node->value.type != ParameterValue::Type::DOUBLE_ARRAY) 
    {
        throw Error(-113,"GetDoubleArray: ключ не найден или неверный тип: " + key);
    }

    return std::get<std::vector<double>>(node->value.value);
}

const std::string& ParameterContainer::GetString(const std::string& key) const 
{
    Node* node = findNode(root_.get(), key);

    if (!node || node->value.type != ParameterValue::Type::STRING) 
    {
        throw Error(-114,"GetString: ключ не найден или неверный тип: " + key);
    }

    return std::get<std::string>(node->value.value);
}


void ParameterContainer::insert(const std::string& key, const ParameterValue& value) 
{
    root_ = insertNodeIterative(std::move(root_), key, value);
}

std::unique_ptr<Node> ParameterContainer::insertNodeIterative(std::unique_ptr<Node> root, const std::string& key, const ParameterValue& value)
{
    if (!root) 
    {
        return std::make_unique<Node>(key, value);
    }

    std::unique_ptr<Node>* current = &root;

    while (*current) 
    {
        if (key < (*current)->key) 
        {
            current = &((*current)->left);
        } else if (key > (*current)->key) {
            current = &((*current)->right);
        } else {
            // Ключ уже существует - обновляем значение
            (*current)->value = value;
            return root; // Возвращаем корень, так как дерево не изменилось структурно
        }
    }

    *current = std::make_unique<Node>(key, value);
    return root;
}

void ParameterContainer::clearTree(std::unique_ptr<Node>& node) 
{
    if (node) 
    {
        clearTree(node->left);
        clearTree(node->right);
        node.reset(); //Освобождаем память
    }
}