#include "database.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

// Глобальный объект базы данных
Database g_db;

// Вспомогательная функция для удаления пробелов
std::string trim_main(const std::string& str) {
    const auto strBegin = str.find_first_not_of(" \t\n\r\f\v");
    if (strBegin == std::string::npos)
        return ""; 
    const auto strEnd = str.find_last_not_of(" \t\n\r\f\v");
    const auto strRange = strEnd - strBegin + 1;
    return str.substr(strBegin, strRange);
}

// Главная функция
int main(int argc, char* argv[]) {

    std::string command_line;

    // Основной цикл обработки команд
    while (std::getline(std::cin, command_line)) {
        std::string trimmed_command = trim_main(command_line);

        if (trimmed_command.empty()) {
            std::cout << "__END_OF_CPP_OUTPUT__" << std::endl;
            std::cout.flush();
            continue;
        }

        std::string lower_command_check = trimmed_command;
        std::transform(lower_command_check.begin(), lower_command_check.end(), lower_command_check.begin(),
                       [](unsigned char c){ return std::tolower(c); });

        if (lower_command_check == "exit_server_mode") {
            break; 
        }
        
        try {
            g_db.processCommand(trimmed_command); // Вызов метода объекта Database
        } catch (const std::exception& e) {
            std::cout << "CPP_EXCEPTION: " << e.what() << std::endl; 
        } catch (...) {
            std::cout << "CPP_EXCEPTION: Unknown C++ exception occurred" << std::endl;
        }
        
        std::cout << "__END_OF_CPP_OUTPUT__" << std::endl; // Маркер для сервера
        std::cout.flush(); 
        std::cerr.flush(); 
    }

    return 0;
}