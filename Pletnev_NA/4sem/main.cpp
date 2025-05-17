#include "Database.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

std::map<std::string, int> parseHours(const std::string& input) {
    std::map<std::string, int> hours;
    std::stringstream ss(input);
    std::string pair;
    while (std::getline(ss, pair, ',')) {
        size_t colon = pair.find(':');
        if (colon == std::string::npos) throw Database::InvalidInput("Неправильный формат: " + pair);
        std::string category = pair.substr(0, colon);
        std::string value = pair.substr(colon + 1);
        category.erase(remove_if(category.begin(), category.end(), ::isspace), category.end());
        try {
            hours[category] = std::stoi(value);
        } catch (...) {
            throw Database::InvalidInput("Нечисловое значение: " + value);
        }
    }
    return hours;
}

std::vector<std::string> parseColumns(const std::string& input) {
    std::vector<std::string> columns;
    std::stringstream ss(input);
    std::string col;
    while (std::getline(ss, col, ',')) {
        col.erase(remove_if(col.begin(), col.end(), ::isspace), col.end());
        if (!col.empty()) columns.push_back(col);
    }
    return columns;
}

void showSubMenu(const std::string& title) {
    std::cout << "\n=== " << title << " ==="
              << "\n1. Продолжить"
              << "\n2. Назад"
              << "\nВыберите действие: ";
}

void manageGroups(Database& db) {
    int subChoice;
    do {
        std::cout << "\n=== Управление группами ==="
                  << "\n1. Добавить группу"
                  << "\n2. Удалить группу"
                  << "\n3. Назад"
                  << "\nВыберите действие: ";
        std::cin >> subChoice;
        std::cin.ignore();

        if (subChoice == 3) break;

        std::string name, group;
        std::cout << "Имя сотрудника: ";
        std::getline(std::cin, name);
        std::cout << "Группа: ";
        std::getline(std::cin, group);

        try {
            if (subChoice == 1) db.addGroupToEmployee(name, group);
            else if (subChoice == 2) db.removeGroupFromEmployee(name, group);
            else std::cout << "Неверный выбор!\n";
        } catch (const Database::InvalidInput& e) {
            std::cerr << "[ОШИБКА] " << e.what() << "\n";
        }
    } while (true);
}

void manageStudents(Database& db) {
    int subChoice;
    do {
        std::cout << "\n=== Управление студентами ==="
                  << "\n1. Добавить студента"
                  << "\n2. Удалить студента"
                  << "\n3. Назад"
                  << "\nВыберите действие: ";
        std::cin >> subChoice;
        std::cin.ignore();

        if (subChoice == 3) break;

        std::string empName, studentName;
        std::cout << "Имя сотрудника: ";
        std::getline(std::cin, empName);

        try {
            if (subChoice == 1) {
                Student s;
                std::cout << "Имя студента: ";
                std::getline(std::cin, s.name);
                std::cout << "Группа: ";
                std::cin >> s.group;
                std::cout << "Рейтинг: ";
                std::cin >> s.rating;
                db.addStudent(empName, s);
            } else if (subChoice == 2) {
                std::cout << "Имя студента: ";
                std::getline(std::cin, studentName);
                db.removeStudent(empName, studentName);
            } else {
                std::cout << "Неверный выбор!\n";
            }
        } catch (const Database::InvalidInput& e) {
            std::cerr << "[ОШИБКА] " << e.what() << "\n";
        }
    } while (true);
}

void showMenu() {
    std::cout << "\n=== Главное меню ==="
              << "\n1. Добавить нагрузку"
              << "\n2. Добавить сотрудника"
              << "\n3. Назначить нагрузку"
              << "\n4. Управление группами"
              << "\n5. Управление расписанием"
              << "\n6. Управление студентами"
              << "\n7. Сгенерировать отчет"
              << "\n8. Удалить сотрудника"
              << "\n9. Выход"
              << "\nВыберите действие: ";
}

int main() {
    Database db;
    int choice = 0;
    HierarchyNode* root = new HierarchyNode("Университет");
    db.root = root;

    while (true) {
        try {
            showMenu();
            std::cin >> choice;
            std::cin.ignore();

            if (choice == 9) break;

            std::string name, role, input;
            switch (choice) {
                case 1: {
                    // ... (код добавления нагрузки с возможностью вернуться)
                    int subChoice;
                    do {
                        showSubMenu("Добавление нагрузки");
                        std::cin >> subChoice;
                        std::cin.ignore();
                        if (subChoice == 2) break;

                        std::cout << "Название нагрузки: ";
                        std::getline(std::cin, name);
                        std::cout << "Категории и часы: ";
                        std::getline(std::cin, input);
                        db.addWorkload(name, parseHours(input));
                    } while (true);
                    break;
                }
                case 4: manageGroups(db); break;
                case 6: manageStudents(db); break;
                // ... (аналогично для других пунктов)
                default: std::cout << "Неверный выбор!\n";
            }
        } catch (const Database::InvalidInput& e) {
            std::cerr << "\n[ОШИБКА] " << e.what() << "\n";
        }
    }

    delete root;
    return 0;
}