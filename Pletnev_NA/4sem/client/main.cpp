#include "database.h"
#include <iostream>
#include <string>
#include <algorithm>

Database g_db;

std::string trim_main(const std::string& str) {
    const std::string whitespace = " \t\n\r\f\v";
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // Пустая строка или только пробелы
    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;
    return str.substr(strBegin, strRange);
}


int main() {
    std::string command_line;

    while (std::getline(std::cin, command_line)) {
        std::string trimmed_command = trim_main(command_line);

        if (trimmed_command.empty()) {
            continue;
        }

        // Специальная команда для завершения работы серверной C++ программы
        std::string lower_command = trimmed_command;
        std::transform(lower_command.begin(), lower_command.end(), lower_command.begin(),
                       [](unsigned char c){ return std::tolower(c); });

        if (lower_command == "exit_server_mode") {
            // Перед выходом можно сохранить состояние БД, если это требуется
            break; 
        }
        

        try {
            g_db.processCommand(trimmed_command); // processCommand должен писать в std::cout
        } catch (const std::exception& e) {
            std::cerr << "CPP_ERROR: " << e.what() << std::endl; // Ошибки в stderr
        } catch (...) {
            std::cerr << "CPP_ERROR: Unknown C++ exception occurred" << std::endl;
        }
        
        // Добавляем маркер конца вывода, чтобы сервер знал, когда C++ закончил отвечать
        std::cout << "__END_OF_CPP_OUTPUT__" << std::endl;
        std::cout.flush(); // Важно для небуферизованного вывода
        std::cerr.flush(); // И для ошибок
    }

    return 0;
}