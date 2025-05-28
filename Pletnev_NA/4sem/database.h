#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

struct Workload {
    std::string name;
    std::string hours;
};

struct Employee {
    std::string name;
    std::unordered_map<int, int> workloads; // workload index -> hours
};

class TreeNode {
public:
    std::string name;
    std::vector<std::unique_ptr<TreeNode>> children;
    std::vector<Employee> employees;
    
    TreeNode(const std::string& name) : name(name) {}
};

class Database {
private:
    std::unique_ptr<TreeNode> root;
    std::vector<Workload> workloads;
    
    TreeNode* findOrCreateNode(const std::string& path);
    void printTable(const std::vector<Employee*>& employees, 
                  const std::vector<std::string>& columns) const;
public:
    Database();
    
    void addWorkload(const std::string& name, const std::string& hours);
    void addNode(const std::string& path);
    void addEmployee(const std::string& path, const std::string& name, 
                    const std::vector<std::pair<int, int>>& workloadEntries);
    std::vector<Employee*> getEmployees(const std::string& nodeName) const;
    const Workload& getWorkload(int index) const;
    void processCommand(const std::string& command);
};

#endif