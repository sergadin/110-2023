#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <functional>
#include <set>
#include <map>

// Структура для учебного предмета
struct Subject {
    std::string id;
    std::string name;
};

// Структура для записи в расписании
struct ScheduleEntry {
    std::string subject_id;
    std::string activity_type; // лекция, семинар, лаба и т.д.
    std::string day_of_week;
    std::string time_slot;     // Например, "09:00-10:30"
    std::string room;          // Может быть пустой

    // Для удобства сравнения и хранения в set/сортировки
    bool operator<(const ScheduleEntry& other) const {
        if (day_of_week != other.day_of_week) return day_of_week < other.day_of_week; // Сначала по дню
        if (time_slot != other.time_slot) return time_slot < other.time_slot; // Затем по времени
        if (subject_id != other.subject_id) return subject_id < other.subject_id;
        if (activity_type != other.activity_type) return activity_type < other.activity_type;
        return room < other.room;
    }
};

// Структура для сотрудника (дополнена)
struct Employee {
    std::string name;
    std::vector<std::pair<std::string, int>> workload; // Базовая нагрузка
    std::set<std::string> assigned_subject_ids;       // ID назначенных предметов
    // Расписание: ключ - день недели (строка), значение - вектор записей расписания на этот день
    std::map<std::string, std::vector<ScheduleEntry>> schedule_by_day; // Ключ - день недели (например, "monday")
};

// Структура для узла иерархии (без изменений)
struct Node {
    std::string name;
    std::unordered_map<std::string, Node*> children;
    std::vector<Employee> employees;

    Node(const std::string& n = "") : name(n) {}
};

// Основной класс базы данных
class Database {
private:
    Node* root; // Корневой узел
    std::unordered_map<std::string, Subject> subject_catalog; // Каталог всех предметов

    // Приватные вспомогательные методы
    std::string toLower(const std::string& str) const; // Уже есть
    std::vector<std::string> tokenize(const std::string& cmd) const; // Уже есть
    void deleteTree(Node* node); // Уже есть
    Node* getNode(const std::string& path); // Уже есть
    Node* createNodeByPath(const std::string& path); // Уже есть
    
    // Изменен для возврата вектора указателей на Employee, чтобы их можно было модифицировать
    void getAllEmployeesRecursive(Node* node, std::vector<Employee*>& emp_list); 
    
    // Вспомогательная функция для поиска сотрудника
    Employee* findEmployee(const std::string& node_path, const std::string& employee_name);

    // Вспомогательная функция для проверки конфликтов времени для сотрудника
    bool checkTimeSlotConflict(const Employee* employee, const std::string& day, const std::string& time_slot) const;
    
    // Вспомогательная функция для получения индекса дня недели (для сортировки)
    int dayOfWeekToIndex(const std::string& day) const;


public:
    Database();
    ~Database();

    // Публичная утилита (остается публичной для Validation)
    std::vector<std::string> splitPath(const std::string& path) const;
    // Добавим toLowerInternal для использования в Validation без выноса toLower в public
    std::string toLowerInternal(const std::string& str) const;


    // Существующие публичные методы API
    void addNode(const std::string& path);
    void addEmployee(const std::string& path, const std::string& name,
                     const std::vector<std::pair<std::string, int>>& workload);
    void query(const std::vector<std::string>& columns, const std::string& path, bool row_sum = false);
    void save(const std::string& filename) const; // Будет обновлен
    void load(const std::string& filename); // Будет обновлен
    void processCommand(const std::string& command); // Будет обновлен

    void removeNode(const std::string& path, bool recursive = false);
    void removeEmployee(const std::string& node_path, const std::string& employee_name);
    void editEmployeeWorkload(const std::string& node_path, const std::string& employee_name,
                              const std::vector<std::pair<std::string, int>>& new_workload);

    // Новые публичные методы для предметов и расписания
    void addSubject(const std::string& id, const std::string& name);
    void listSubjects() const;
    void assignSubjectToEmployee(const std::string& node_path, const std::string& employee_name, const std::string& subject_id);
    void addScheduleEntry(const std::string& node_path, const std::string& employee_name,
                          const std::string& subject_id, const std::string& activity_type,
                          const std::string& day, const std::string& time_slot, const std::string& room);
    void viewSchedule(const std::string& node_path, const std::string& employee_name) const;
    
    void resetDatabase(); // Для очистки базы (полезно для тестов)
};

#endif