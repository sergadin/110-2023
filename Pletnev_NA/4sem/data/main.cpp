#include "database.h"
#include <iostream>
#include <string>
#include <algorithm>

void printHelp() {
    std::cout << "=== University Workload Database Management System ===" << std::endl;
    std::cout << "Available commands:" << std::endl;
    std::cout << "  add node <path> - Add an organizational node, e.g., 'faculty/science/math'" << std::endl;
    std::cout << "  add employee <path> <name> <type>:<hours> ... - Add an employee with workload, e.g., 'add employee faculty/science/math 'Ivanov I.I.' lectures:48 seminars:32'" << std::endl;
    std::cout << "  query columns <cols> where <node> [row_sum] - Query data, e.g., 'query columns name lectures seminars where math row_sum'" << std::endl;
    std::cout << "  load <filename> - Load database from file" << std::endl;
    std::cout << "  save <filename> - Save database to file" << std::endl;
    std::cout << "  help - Show this help message" << std::endl;
    std::cout << "  exit - Exit the program" << std::endl;
}

int main() {
    Database db;
    std::cout << "=== University Workload Database Management System ===" << std::endl;
    std::cout << "Type 'help' for commands or 'exit' to quit." << std::endl;
    printHelp();
    std::string command;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);
        if (command.empty()) continue;
        std::string cmd = command;
        std::transform(cmd.begin(), cmd.end(), cmd.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        if (cmd == "exit") {
            break;
        } else if (cmd == "help") {
            printHelp();
        } else {
            try {
                db.processCommand(command);
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
    }
    std::cout << "Exiting database system. Goodbye!" << std::endl;
    return 0;
}