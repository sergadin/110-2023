#include "ParameterContainer.h"

ParameterValue parseValue(const std::string& valueStr, const ParameterContainer& container);
std::string concatenateStringsStream(const std::vector<std::string>& strings);
std::vector<std::string> splitStringManual(const std::string& str, char delimiter);
std::string toString(const ParameterValue& param);
std::string toString(const char* value);

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
            insert(key, parseValue(valueStr, *this));

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
ParameterValue parseValue(const std::string& valueStr, const ParameterContainer& container)
{
    ParameterValue result; // Создаем объект для результата

    // Проверяем, является ли строка массивом (начинается с '[' и заканчивается ']')
    if (valueStr[0] == '[' && valueStr.back() == ']') 
    {
        std::string innerStr = valueStr.substr(1, valueStr.length() - 2);
        std::vector<std::string> STR = splitStringManual(innerStr, ',');
        size_t n = STR.size();
        std::vector<std::string> STR2;

        for (size_t i = 0; i < n; ++i) 
        {
            bool isDollar = std::any_of(STR[i].begin(), STR[i].end(), [](char c){ return c == '$'; });
            std::vector<std::string> processedSTR_1;

            if (!isDollar) {
                    processedSTR_1.push_back(STR[i]);
            } else {
                std::vector<std::string> STR_1 = splitStringManual(STR[i], '$');
                processedSTR_1.push_back(STR_1[0]);
                for (size_t j = 1; j < STR_1.size(); j++) 
                {
                    std::optional<ParameterValue> strI = container.GetValue(STR_1[j]);

                    if (strI.has_value()) {
                        processedSTR_1.push_back(toString(strI.value()));
                    } else {
                        throw Error(-109,"Ключ не найден:" + STR_1[j]);
                    }
                }
            }
            
            STR2.push_back(concatenateStringsStream(processedSTR_1) + ',');
        }

        std::string innerStr_1 = concatenateStringsStream(STR2);
        innerStr_1 = innerStr_1.substr(0, valueStr.length() - 1);
        bool isDouble = std::any_of(innerStr_1.begin(), innerStr_1.end(), [](char c){ return c == '.'; });

        // Выбираем функцию разбора в зависимости от наличия десятичной точки
        if (isDouble) 
        {
            try
            {
                std::vector<double> dArray = container.doubleArrayGet(innerStr_1);
                result.value = dArray;
                result.type = ParameterValue::Type::DOUBLE_ARRAY;
            } catch (const std::invalid_argument& e) {
                result.value = "[" + innerStr_1 + "]";
                result.type = ParameterValue::Type::STRING;
            }
            
        } else {

            try
            {
                std::vector<int> iArray = container.intArrayGet(innerStr_1);
                result.value = iArray;
                result.type = ParameterValue::Type::INT_ARRAY;
            } catch (const std::invalid_argument& e) {
                result.value = "[" + innerStr_1 + "]";
                result.type = ParameterValue::Type::STRING;
            }
            
        }

    } else { // Разбор одиночного значения

        bool isDollar = std::any_of(valueStr.begin(), valueStr.end(), [](char c){ return c == '$'; });
        std::vector<std::string> STR2; //Corrected: Initialize STR2

        if (!isDollar) {
                    STR2.push_back(valueStr);
        } else {
            std::vector<std::string> STR = splitStringManual(valueStr, '$');
            STR2.push_back(STR[0]);
            for (size_t i = 1; i < STR.size(); i++) 
            {
                std::optional<ParameterValue> strI = container.GetValue(STR[i]);

                if (strI.has_value()) {
                    STR2.push_back(toString(strI.value())); 
                } else {
                    throw Error(-109,"Ключ не найден:" + STR[i]);
                }
            }
        }

        std::string innerStr = concatenateStringsStream(STR2);

        if (innerStr.find('.') != std::string::npos) 
        {
            try 
            {
                result.value = container.doubleGet(innerStr);
                result.type = ParameterValue::Type::DOUBLE;
            } catch (const Error& e) {
                result.value = innerStr;
                result.type = ParameterValue::Type::STRING;
            }

        } else {
            
            try 
            {
                result.value = container.intGet(innerStr);
                result.type = ParameterValue::Type::INT;
            } catch (const Error& e) {
                result.value = innerStr;
                result.type = ParameterValue::Type::STRING;
            }
        }
    }

    return result;
}

std::optional<ParameterValue> ParameterContainer::GetValue(const std::string& key) const 
{
    Node* node = findNode(root_.get(), key);
    if (node != nullptr) 
    {
        return node->value;
    } else {
        return std::nullopt;
    }
}

template <typename T>
std::string toString(const T& value) 
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

std::string toString(const ParameterValue& param) 
{
    std::stringstream ss;
    std::visit([&](const auto& val) 
    {
        using T = std::decay_t<decltype(val)>;

        if constexpr (std::is_same_v<T, int>) 
        {
            ss << std::get<int>(param.value);
        } else if constexpr (std::is_same_v<T, double>) {
            ss << std::get<double>(param.value);
        } else if constexpr (std::is_same_v<T, std::string>) {
            ss << std::get<std::string>(param.value);
        } else {
            ss << "Unsupported ParameterValue type";
        }
    }, param.value);

    return ss.str();
}

//Специально для строк C
std::string toString(const char* value) 
{
    return value ? std::string(value) : "";
}

std::string concatenateStringsStream(const std::vector<std::string>& strings) 
{
    std::stringstream ss;
    for (const auto& str : strings) 
    {
        ss << str;
    }
    return ss.str();
}

std::vector<std::string> splitStringManual(const std::string& str, char delimiter) 
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) 
    {
        tokens.push_back(token);
    }
    return tokens;
}

int ParameterContainer::parseInt(const std::string& valueStr) const 
{
    std::string currentNum;
    int count_minus = 0;
    for (char c : valueStr) 
    {
        if (isdigit(c) || c == '-') 
        {
            currentNum += c;
        } else if (c == '-') {
            count_minus++;
            if (count_minus > 1)
            {
                throw Error(-305, "parseInt: в числе два минуса");
            }
            currentNum += c;
        } else {
            throw Error(-322, "parseInt: Не цифры в занчение");
        }
    }

    return std::stoi(currentNum);
}

double ParameterContainer::parseDouble(const std::string& valueStr) const 
{
    std::string currentNum;
    int count_dot = 0;
    int count_minus = 0;
    for (char c : valueStr) 
    {
        if (isdigit(c)) 
        {
            currentNum += c;
        } else if (c == '.') {
            count_dot++;
            if (count_dot > 1)
            {
                throw Error(-305, "parseDouble: в числе две точки");
            }
            currentNum += c;
        } else if (c == '-') {
            count_minus++;
            if (count_minus > 1)
            {
                throw Error(-305, "parseDouble: в числе два минуса");
            }
            currentNum += c;
        } else {
            throw Error(-322, "parseDouble: Не цифры в занчение");
        }
    }

    return std::stod(currentNum);
}

std::vector<int> ParameterContainer::parseIntArray(const std::string& valueStr) const 
{
    std::vector<int> arr;
    std::string currentNum;
    int count_minus = 0;

    for (char c : valueStr) 
    {
        if (isdigit(c)) 
        {
            currentNum += c;
        } else if (c == '-') {
            count_minus++;
            if (count_minus > 1)
            {
                throw Error(-305, "parseIntArray: в числе два минуса");
            }
            currentNum += c;
        } else if (c == ',') {
            if (!currentNum.empty()) 
            {
                try 
                {
                    arr.push_back(std::stoi(currentNum));
                    currentNum.clear();
                } catch (const std::invalid_argument& e) {
                    throw Error(-301, "parseIntArray: Недопустимое значение в массиве");
                } catch (const std::out_of_range& e) {
                    throw Error(-302, "parseIntArray: Целочисленное значение вне диапазона в массиве");
                }
            }
        }
    }

    // Обработка последнего числа
    if (!currentNum.empty()) 
    {
        try 
        {
            arr.push_back(std::stoi(currentNum));
        } catch (const std::invalid_argument& e) {
            throw Error(-301, "parseIntArray: недопустимое значение в массиве");
        } catch (const std::out_of_range& e) {
            throw Error(-302, "parseIntArray: значение вне диапазона в массиве");
        }
    }

    return arr;
}


std::vector<double> ParameterContainer::parseDoubleArray(const std::string& valueStr) const 
{
    std::vector<double> arr;
    std::string currentNum;
    int count_dot = 0;
    for (char c : valueStr) 
    {
        if (isdigit(c) || c == '-') 
        {
            currentNum += c;
        } else if (c == '.')
        {
            count_dot++;
            if (count_dot > 1)
            {
                throw Error(-305, "parseDoubleArray: в числе две точки");
            }
            currentNum += c;
        } else if (c == ',') {
            if (!currentNum.empty()) {
                try {
                    arr.push_back(std::stod(currentNum));
                    currentNum.clear();
                } catch (const std::invalid_argument& e) {
                    throw Error(-303, "parseDoubleArray: недопустимое  значение в массиве");
                } catch (const std::out_of_range& e) {
                    throw Error(-304, "parseDoubleArray: значение вне диапазона в массиве");
                }
            }
            count_dot = 0;
        }
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
    if (!node) return nullptr;          // Базовый случай: узел не найден
    if (key == node->key) return node;  // Базовый случай: ключ найден
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