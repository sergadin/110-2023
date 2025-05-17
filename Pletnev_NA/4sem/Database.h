#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <set>

struct Student {
    std::string name;
    int group;
    double rating;

    Student(const std::string& n = "", int g = 0, double r = 0.0)
        : name(n), group(g), rating(r) {}
};

struct HierarchyNode {
    std::string name;
    std::vector<HierarchyNode*> children;
    HierarchyNode* parent;
    bool isEmployee;
    std::string role;

    HierarchyNode(const std::string& n, HierarchyNode* p = nullptr, bool emp = false)
        : name(n), parent(p), isEmployee(emp) {}
};

struct Workload {
    std::string name;
    std::map<std::string, int> hours;
};

struct Employee {
    std::string name;
    HierarchyNode* node;
    std::vector<std::pair<int, int>> workloads;
    std::vector<std::string> groups;
    std::map<std::string, std::vector<std::string>> schedule;
    std::vector<Student> students;
};

class Database {
public:
    std::vector<Workload> workloads;
    std::vector<Employee> employees;
    HierarchyNode* root;

    // Исключения
    class InvalidInput : public std::runtime_error {
    public:
        InvalidInput(const std::string& msg) : runtime_error(msg) {}
    };
    class EmployeeNotFound : public InvalidInput {
    public: EmployeeNotFound(const std::string& name) : InvalidInput("Сотрудник не найден: " + name) {}
    };
    class WorkloadNotFound : public InvalidInput {
    public: WorkloadNotFound(const std::string& name) : InvalidInput("Нагрузка не найдена: " + name) {}
    };
    class InvalidCategory : public InvalidInput {
    public: InvalidCategory(const std::string& name) : InvalidInput("Несуществующая категория: " + name) {}
    };
    class DuplicateEntry : public InvalidInput {
    public: DuplicateEntry(const std::string& name) : InvalidInput("Дублирование: " + name) {}
    };
    class InvalidRole : public InvalidInput {
    public: InvalidRole(const std::string& role) : InvalidInput("Роль не существует: " + role) {}
    };
    class EmptyField : public InvalidInput {
    public: EmptyField(const std::string& field) : InvalidInput("Пустое поле: " + field) {}
    };

    Database();
    ~Database();

    void addWorkload(const std::string& name, const std::map<std::string, int>& hours);
    void addEmployee(const std::string& name, HierarchyNode* node);
    void assignWorkload(const std::string& empName, const std::string& workloadName, int count);
    void addGroupToEmployee(const std::string& empName, const std::string& group);
    void removeGroupFromEmployee(const std::string& empName, const std::string& group);
    void setSchedule(const std::string& empName, const std::string& day, const std::string& timeSlot);
    void addStudent(const std::string& empName, const Student& student);
    void removeStudent(const std::string& empName, const std::string& studentName);
    void deleteEmployee(const std::string& empName);
    std::vector<Employee*> selectByRole(const std::string& role);
    std::string generateReport(const std::vector<std::string>& columns, const std::string& role);

private:
    void _deleteHierarchy(HierarchyNode* node);
    int _findWorkloadIndex(const std::string& name);
    int _findEmployeeIndex(const std::string& name);
    bool _roleExists(const std::string& role);
    void _validateHours(const std::map<std::string, int>& hours);
    std::string _trim(const std::string& str);
    Employee& _getEmployee(const std::string& empName);
};

#endif