#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <set>
#include <utility>
#include <algorithm>
#include <functional>

// Структура для учебного предмета
struct Subject {
    std::string id;
    std::string name;
};

// Структура для записи в расписании
struct ScheduleEntry {
    std::string subject_id;
    std::string activity_type;
    std::string day_of_week;
    std::string time_slot;    
    std::string room;         

    bool operator<(const ScheduleEntry& other) const {
        if (day_of_week != other.day_of_week) return day_of_week < other.day_of_week;
        if (time_slot != other.time_slot) return time_slot < other.time_slot;
        if (subject_id != other.subject_id) return subject_id < other.subject_id;
        if (activity_type != other.activity_type) return activity_type < other.activity_type;
        return room < other.room;
    }
};

// Структура для сотрудника
struct Employee {
    std::string name;
    std::vector<std::pair<std::string, int>> workload;
    std::set<std::string> assigned_subject_ids;      
    std::map<std::string, std::vector<ScheduleEntry>> schedule_by_day; 
};

// Структура для узла иерархии
struct Node {
    std::string name;
    std::unordered_map<std::string, Node*> children;
    std::vector<Employee> employees;

    Node(const std::string& n = "") : name(n) {}
};

// Основной класс базы данных
class Database {
private:
    Node* root;
    std::unordered_map<std::string, Subject> subject_catalog;

    std::string toLower(const std::string& str) const;
    std::vector<std::string> tokenize(const std::string& cmd) const;
    void deleteTree(Node* node);
    Node* getNode(const std::string& path);
    Node* createNodeByPath(const std::string& path);
    void getAllEmployeesRecursive(Node* node, std::vector<Employee*>& emp_list); 
    Employee* findEmployee(const std::string& node_path, const std::string& employee_name);
    bool checkTimeSlotConflict(const Employee* employee, const std::string& day, const std::string& time_slot) const;
    int dayOfWeekToIndex(const std::string& day) const;
    void displayHelpInformation() const; // Сделаем const и вынесем определение в .cpp

public:
    Database();
    ~Database();

    std::vector<std::string> splitPath(const std::string& path) const;
    std::string toLowerInternal(const std::string& str) const; // Для Validation

    void addNode(const std::string& path);
    void addEmployee(const std::string& path, const std::string& name,
                     const std::vector<std::pair<std::string, int>>& workload);
    void query(const std::vector<std::string>& columns, const std::string& path, bool row_sum = false);
    void save(const std::string& filename) const;
    void load(const std::string& filename);
    void processCommand(const std::string& command);

    void removeNode(const std::string& path, bool recursive = false);
    void removeEmployee(const std::string& node_path, const std::string& employee_name);
    void editEmployeeWorkload(const std::string& node_path, const std::string& employee_name,
                              const std::vector<std::pair<std::string, int>>& new_workload);

    void addSubject(const std::string& id, const std::string& name);
    void listSubjects() const;
    void assignSubjectToEmployee(const std::string& node_path, const std::string& employee_name, const std::string& subject_id);
    void addScheduleEntry(const std::string& node_path, const std::string& employee_name,
                          const std::string& subject_id, const std::string& activity_type,
                          const std::string& day, const std::string& time_slot, const std::string& room);
    void viewSchedule(const std::string& node_path, const std::string& employee_name) const;
    
    void resetDatabase();
};

#endif