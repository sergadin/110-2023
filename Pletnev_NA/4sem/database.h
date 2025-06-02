#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <functional>

// Структура для сотрудника
struct Employee {
    std::string name;
    std::vector<std::pair<std::string, int>> workload;
};

// Структура для узла иерархии
struct Node {
    std::string name;
    std::unordered_map<std::string, Node*> children;
    std::vector<Employee> employees;

    Node(const std::string& n = "") : name(n) {} // Конструктор
};

// Основной класс базы данных
class Database {
private:
    Node* root; // Корневой узел

    // Приватные вспомогательные методы
    std::string toLower(const std::string& str) const;
    std::vector<std::string> tokenize(const std::string& cmd) const;
    void deleteTree(Node* node); // Рекурсивное удаление поддерева
    Node* getNode(const std::string& path); // Получение узла по пути
    Node* createNodeByPath(const std::string& path); // Создание узла по пути
    std::vector<Employee> getAllEmployeesRecursive(Node* node) const; // Сбор всех сотрудников

public:
    Database();  // Конструктор
    ~Database(); // Деструктор

    // Публичные утилиты и API
    std::vector<std::string> splitPath(const std::string& path) const; // Разделение пути на компоненты

    void addNode(const std::string& path);
    void addEmployee(const std::string& path, const std::string& name,
                     const std::vector<std::pair<std::string, int>>& workload);
    void query(const std::vector<std::string>& columns, const std::string& path, bool row_sum = false);
    void save(const std::string& filename) const;
    void load(const std::string& filename);
    void processCommand(const std::string& command); // Главный обработчик команд

    // Новые операции
    void removeNode(const std::string& path, bool recursive = false);
    void removeEmployee(const std::string& node_path, const std::string& employee_name);
    void editEmployeeWorkload(const std::string& node_path, const std::string& employee_name,
                              const std::vector<std::pair<std::string, int>>& new_workload);
};

#endif