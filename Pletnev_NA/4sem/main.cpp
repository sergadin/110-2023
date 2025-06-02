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

// Функция для удаления начальных и конечных пробелов
std::string trim_main(const std::string& str) {
    const auto strBegin = str.find_first_not_of(" \t\n\r\f\v");
    if (strBegin == std::string::npos)
        return ""; 
    const auto strEnd = str.find_last_not_of(" \t\n\r\f\v");
    const auto strRange = strEnd - strBegin + 1;
    return str.substr(strBegin, strRange);
}


int main(int argc, char* argv[]) {
    #ifdef _WIN32
    // Устанавливаем кодировку вывода консоли в UTF-8 для Windows
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8); // Также для ввода, на всякий случай
    #endif

    std::string command_line;

    while (std::getline(std::cin, command_line)) {
        std::string trimmed_command = trim_main(command_line);

        if (trimmed_command.empty()) {
            // Пустая команда от сервера, можно проигнорировать или ответить пустым маркером
            std::cout << "__END_OF_CPP_OUTPUT__" << std::endl;
            std::cout.flush();
            continue;
        }

        std::string lower_command_check = trimmed_command;
        std::transform(lower_command_check.begin(), lower_command_check.end(), lower_command_check.begin(),
                       [](unsigned char c){ return std::tolower(c); });

        // Специальная команда от сервера Python для завершения этого C++ процесса
        if (lower_command_check == "exit_server_mode") {
            // Можно добавить сохранение перед выходом, если требуется
            break; 
        }
        
        try {
            g_db.processCommand(trimmed_command); 
        } catch (const std::exception& e) {
            // Ошибки из Database::processCommand или глубже должны выводиться в std::cout или std::cerr там же.
            // Если они бросают исключения, которые мы хотим передать серверу:
            std::cout << "CPP_EXCEPTION: " << e.what() << std::endl; 
        } catch (...) {
            std::cout << "CPP_EXCEPTION: Unknown C++ exception occurred" << std::endl;
        }
        
        // Важно: маркер конца вывода после КАЖДОЙ обработанной команды
        std::cout << "__END_OF_CPP_OUTPUT__" << std::endl;
        std::cout.flush(); // Принудительный сброс буфера stdout
        std::cerr.flush(); // Также сбрасываем stderr на всякий случай
    }

    return 0;
}