#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <functional>

// Перечисление для дней недели
enum class DayOfWeek {
    MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, UNKNOWN
};

// Вспомогательные функции для DayOfWeek
std::string dayOfWeekToString(DayOfWeek day);
DayOfWeek stringToDayOfWeek(const std::string& s);

// Структура для предмета
struct Subject {
    std::string id;
    std::string name;
};

// Структура для занятия в расписании
struct ScheduledClass {
    std::string subject_id;
    std::string class_type; // "лекция", "семинар" и т.д.
    DayOfWeek day;
    std::string time_slot;  // Например, "09:00-10:30" или "1"
    std::string room;       // Опционально
};

// Обновленная структура для сотрудника
struct Employee {
    std::string name;
    std::vector<std::pair<std::string, int>> workload; // Суммарная нагрузка
    std::vector<ScheduledClass> schedule;             // Расписание на неделю
    std::vector<std::string> taught_subject_ids;      // ID предметов, которые ведет преподаватель
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
    std::unordered_map<std::string, Subject> subjects_catalog_; // Хранилище предметов

    // Вспомогательные приватные методы
    std::string toLower(const std::string& str) const;
    std::vector<std::string> tokenize(const std::string& cmd) const;
    void deleteTree(Node* node);
    Node* getNode(const std::string& path); // Находит узел
    Employee* getEmployee(const std::string& path, const std::string& employee_name); // Находит сотрудника
    Node* createNodeByPath(const std::string& path);
    std::vector<Employee> getAllEmployeesRecursive(Node* node) const;

    // Новые приватные методы для обработчиков команд
    void handleAddSubject(const std::vector<std::string>& args);
    void handleListSubjects(const std::vector<std::string>& args);
    void handleAssignSubject(const std::vector<std::string>& args);
    void handleAddSchedule(const std::vector<std::string>& args);
    void handleViewSchedule(const std::vector<std::string>& args);

public:
    Database();
    ~Database();

    // Публичная утилита для работы с путями (остается публичной)
    std::vector<std::string> splitPath(const std::string& path) const;

    // Публичные методы API (старые + новые для единообразия вызова из processCommand)
    void addNodeCmd(const std::vector<std::string>& args); // Обертка для старого addNode
    void addEmployeeCmd(const std::vector<std::string>& args); // Обертка для старого addEmployee
    void queryCmd(const std::vector<std::string>& args); // Обертка для старого query

    void save(const std::string& filename) const;
    void load(const std::string& filename);
    void processCommand(const std::string& command);
};

#endif