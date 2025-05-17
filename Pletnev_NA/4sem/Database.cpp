#include "Database.h"
#include <cctype>

Database::Database() : root(nullptr) {}

Database::~Database() {
    _deleteHierarchy(root);
}

void Database::_deleteHierarchy(HierarchyNode* node) {
    if (!node) return;
    for (auto child : node->children) {
        _deleteHierarchy(child);
    }
    delete node;
}

std::string Database::_trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

void Database::_validateHours(const std::map<std::string, int>& hours) {
    for (const auto& pair : hours) {
        if (pair.second <= 0) {
            throw InvalidInput("Часы для '" + pair.first + "' должны быть положительными");
        }
    }
}

void Database::addWorkload(const std::string& name, const std::map<std::string, int>& hours) {
    std::string trimmedName = _trim(name);
    if (trimmedName.empty()) throw EmptyField("Название нагрузки");
    if (_findWorkloadIndex(trimmedName) != -1) throw DuplicateEntry(trimmedName);
    if (hours.empty()) throw EmptyField("Часы нагрузки");
    _validateHours(hours);
    workloads.push_back({trimmedName, hours});
}

void Database::addEmployee(const std::string& name, HierarchyNode* node) {
    std::string trimmedName = _trim(name);
    if (trimmedName.empty()) throw EmptyField("Имя сотрудника");
    if (!node->isEmployee) throw InvalidInput("Узел '" + node->name + "' не является сотрудником");
    if (_findEmployeeIndex(trimmedName) != -1) throw DuplicateEntry(trimmedName);
    employees.push_back({trimmedName, node, {}, {}, {}, {}});
}

void Database::assignWorkload(const std::string& empName, const std::string& wlName, int count) {
    if (count <= 0) throw InvalidInput("Количество должно быть положительным");
    int wlIdx = _findWorkloadIndex(_trim(wlName));
    int empIdx = _findEmployeeIndex(_trim(empName));
    if (empIdx == -1) throw EmployeeNotFound(empName);
    if (wlIdx == -1) throw WorkloadNotFound(wlName);
    employees[empIdx].workloads.emplace_back(wlIdx, count);
}

Employee& Database::_getEmployee(const std::string& empName) {
    int idx = _findEmployeeIndex(_trim(empName));
    if (idx == -1) throw EmployeeNotFound(empName);
    return employees[idx];
}

void Database::addGroupToEmployee(const std::string& empName, const std::string& group) {
    Employee& emp = _getEmployee(empName);
    std::string trimmedGroup = _trim(group);
    if (std::find(emp.groups.begin(), emp.groups.end(), trimmedGroup) != emp.groups.end()) {
        throw DuplicateEntry("Группа " + trimmedGroup);
    }
    emp.groups.push_back(trimmedGroup);
}

void Database::removeGroupFromEmployee(const std::string& empName, const std::string& group) {
    Employee& emp = _getEmployee(empName);
    std::string trimmedGroup = _trim(group);
    auto it = std::find(emp.groups.begin(), emp.groups.end(), trimmedGroup);
    if (it == emp.groups.end()) throw InvalidInput("Группа не найдена: " + trimmedGroup);
    emp.groups.erase(it);
}

void Database::setSchedule(const std::string& empName, const std::string& day, const std::string& timeSlot) {
    Employee& emp = _getEmployee(empName);
    std::string trimmedDay = _trim(day);
    std::string trimmedTime = _trim(timeSlot);
    emp.schedule[trimmedDay].push_back(trimmedTime);
}

void Database::addStudent(const std::string& empName, const Student& student) {
    Employee& emp = _getEmployee(empName);
    auto it = std::find_if(emp.students.begin(), emp.students.end(),
        [&](const Student& s) { return s.name == student.name; });
    if (it != emp.students.end()) throw DuplicateEntry("Студент " + student.name);
    emp.students.push_back(student);
}

void Database::removeStudent(const std::string& empName, const std::string& studentName) {
    Employee& emp = _getEmployee(empName);
    std::string trimmedName = _trim(studentName);
    auto it = std::find_if(emp.students.begin(), emp.students.end(),
        [&](const Student& s) { return s.name == trimmedName; });
    if (it == emp.students.end()) throw InvalidInput("Студент не найден: " + trimmedName);
    emp.students.erase(it);
}

void Database::deleteEmployee(const std::string& empName) {
    int idx = _findEmployeeIndex(_trim(empName));
    if (idx == -1) throw EmployeeNotFound(empName);
    employees.erase(employees.begin() + idx);
}

int Database::_findWorkloadIndex(const std::string& name) {
    auto it = std::find_if(workloads.begin(), workloads.end(),
        [&](const Workload& wl) { return wl.name == name; });
    return (it != workloads.end()) ? std::distance(workloads.begin(), it) : -1;
}

int Database::_findEmployeeIndex(const std::string& name) {
    auto it = std::find_if(employees.begin(), employees.end(),
        [&](const Employee& e) { return e.name == name; });
    return (it != employees.end()) ? std::distance(employees.begin(), it) : -1;
}

bool Database::_roleExists(const std::string& role) {
    for (const auto& emp : employees) {
        if (emp.node->role == role) return true;
    }
    return false;
}

std::vector<Employee*> Database::selectByRole(const std::string& role) {
    std::string trimmedRole = _trim(role);
    if (!_roleExists(trimmedRole)) throw InvalidRole(trimmedRole);
    
    std::vector<Employee*> result;
    for (auto& emp : employees) {
        if (emp.node->role == trimmedRole) {
            result.push_back(&emp);
        }
    }
    return result;
}

std::string Database::generateReport(const std::vector<std::string>& columns, const std::string& role) {
    if (columns.empty()) throw EmptyField("Колонки отчета");
    std::set<std::string> uniqueColumns;
    for (const auto& col : columns) {
        std::string trimmedCol = _trim(col);
        if (trimmedCol.empty()) throw EmptyField("Название колонки");
        if (!uniqueColumns.insert(trimmedCol).second) throw InvalidInput("Повторяющаяся колонка: " + trimmedCol);
        if (trimmedCol != "name") {
            bool exists = false;
            for (const auto& wl : workloads) {
                if (wl.hours.count(trimmedCol) > 0) {
                    exists = true;
                    break;
                }
            }
            if (!exists && trimmedCol != "groups" && trimmedCol != "students" && trimmedCol != "schedule") {
                throw InvalidCategory(trimmedCol);
            }
        }
    }

    auto selected = selectByRole(role);
    std::stringstream ss;

    for (const auto& col : columns) ss << col << "\t";
    ss << "\n";

    for (const auto emp : selected) {
        for (const auto& col : columns) {
            std::string trimmedCol = _trim(col);
            if (trimmedCol == "name") {
                ss << emp->name << "\t";
            } else if (trimmedCol == "groups") {
                ss << "[";
                for (size_t i = 0; i < emp->groups.size(); ++i) {
                    ss << emp->groups[i];
                    if (i != emp->groups.size() - 1) ss << ", ";
                }
                ss << "]\t";
            } else if (trimmedCol == "students") {
                ss << "[";
                for (size_t i = 0; i < emp->students.size(); ++i) {
                    ss << emp->students[i].name;
                    if (i != emp->students.size() - 1) ss << ", ";
                }
                ss << "]\t";
            } else if (trimmedCol == "schedule") {
                ss << "{";
                for (const auto& pair : emp->schedule) {
                    const std::string& day = pair.first;
                    const std::vector<std::string>& times = pair.second;
                    ss << day << ": ";
                    for (size_t i = 0; i < times.size(); ++i) {
                        ss << times[i];
                        if (i != times.size() - 1) ss << ", ";
                    }
                    ss << "; ";
                }
                ss << "}\t";
            } else {
                int total = 0;
                for (const auto& wl : emp->workloads) {
                    const auto& hours = workloads[wl.first].hours;
                    auto it = hours.find(trimmedCol);
                    if (it != hours.end()) {
                        total += it->second * wl.second;
                    }
                }
                ss << total << "\t";
            }
        }
        ss << "\n";
    }
    return ss.str();
}