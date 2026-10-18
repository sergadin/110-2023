#include "database.h"
#include "parser.h"
#include <iostream>
#include <string>

int main() {
    StudentDB db;
    SQLParser parser(db);

    std::string line;
    std::cout << ">>> ";
    while (std::getline(std::cin, line)) {
        parser.execute(line);
        std::cout << "\n>>> ";
    }

    return 0;
}
