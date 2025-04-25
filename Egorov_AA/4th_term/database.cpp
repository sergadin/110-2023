#include "database.h"
#include <iostream>

int StudentDB::addStudent(const std::string& name, int group, double gpa, const std::string& info) {
    students.push_back({ nextId, name, group, gpa, info });
    return nextId++;
}

std::optional<Student> StudentDB::getStudentById(int id) {
    for (const auto& s : students) {
        if (s.id == id) return s;
    }
    return std::nullopt;
}

bool StudentDB::deleteStudent(int id) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->id == id) {
            students.erase(it);
            return true;
        }
    }
    return false;
}

void StudentDB::listAll() {
    for (const auto& s : students) {
        s.print();
    }
}
