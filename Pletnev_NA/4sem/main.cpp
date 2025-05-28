#include "database.h"
#include <iostream>
#include <sstream>
#include <limits>

void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    Database db;

    std::cout << "University Workload Database\n";
    std::cout << "Supported commands:\n"
              << "1. add node <path>\n"
              << "2. add workload <path> <name> <workload_name:hours>...\n"
              << "3. query columns <col1> <col2>... where <node>\n"
              << "4. load <filename>\n"
              << "5. save <filename>\n"
              << "6. exit\n"
              << "Example:\n"
              << "add node faculty/math/professor\n"
              << "add workload faculty/math/professor Ivan lectures:48 seminars:32\n"
              << "query columns node_name lectures seminars where professor\n\n";

    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line))
            break;
        if (line.empty())
            continue;
        if (line == "exit")
            break;

        try {
            db.processCommand(line);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    std::cout << "Exiting.\n";
    return 0;
}