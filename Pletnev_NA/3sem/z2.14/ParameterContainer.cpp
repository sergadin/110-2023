#include "ParameterContainer.h"

void ParameterContainer::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw Error(-201, "Could not open file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;

        size_t eqPos = line.find('=');
        if (eqPos == std::string::npos) {
            throw Error(-202, "Incorrect line format: " + line);
        }

        std::string key = trim(line.substr(0, eqPos));
        std::string valueStr = trim(line.substr(eqPos + 1));

        try {
            ParameterValue value;
            if (valueStr[0] == '[' && valueStr.back() == ']') {
               // Обработка массива целых чисел (пример)
               // Более универсальный парсинг массивов должен быть реализован
               std::vector<int> arr;
               std::string trimmedValue = valueStr.substr(1, valueStr.length() - 2);
               std::stringstream ss(trimmedValue);
               int num;
               while (ss >> num) {
                   arr.push_back(num);
                   if (ss.peek() == ',') ss.ignore(); // пропускаем запятые
               }
               value = {ParameterValue::INT_ARRAY, .intArray = new int[arr.size()], .arraySize = arr.size()};
               std::copy(arr.begin(), arr.end(), value.intArray);
            } else {
               // Обработка других типов (double, string)
               try {
                   value = {ParameterValue::DOUBLE, .doubleValue = std::stod(valueStr)};
               } catch (const std::invalid_argument& e) {
                   try {
                       value = {ParameterValue::INT, .intValue = std::stoi(valueStr)};
                   } catch (const std::invalid_argument& e) {
                       value = {ParameterValue::STRING, .stringValue = strdup(valueStr.c_str())};
                   }
               }
            }
            insert(key, value);
        } catch (const Error& e) {
            throw e;
        } catch (const std::exception& e) {
            throw Error(-203, "Error parsing value: " + valueStr + ", error: " + std::string(e.what()));
        }
    }

    file.close();
}