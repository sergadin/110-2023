#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <functional>

struct Employee {
    std::string name;
    std::vector<std::pair<std::string, int>> workload;
};

struct Node {
    std::string name;
    std::unordered_map<std::string, Node*> children;
    std::vector<Employee> employees;

    Node(const std::string& n = "") : name(n) {}
};

class Database {
private:
    Node* root;

    std::string toLower(const std::string& str) const;
    std::vector<std::string> tokenize(const std::string& cmd) const;
    void deleteTree(Node* node);
    Node* getNode(const std::string& path);
    Node* createNodeByPath(const std::string& path);
    std::vector<Employee> getAllEmployeesRecursive(Node* node) const;

public:
    Database();
    ~Database();

    std::vector<std::string> splitPath(const std::string& path) const; // Сделан публичным

    void addNode(const std::string& path);
    void addEmployee(const std::string& path, const std::string& name,
                     const std::vector<std::pair<std::string, int>>& workload);
    void query(const std::vector<std::string>& columns, const std::string& path, bool row_sum = false);
    void save(const std::string& filename) const;
    void load(const std::string& filename);
    void processCommand(const std::string& command);
};

#endif