#ifndef DATABASE_H
#define DATABASE_H

#include "student.h"
#include <vector>
#include <optional>

class StudentDB {
    std::vector<Student> students;
    int nextId = 1;

public:
    int addStudent(const std::string& name, int group, double gpa, const std::string& info);
    std::optional<Student> getStudentById(int id);
    bool deleteStudent(int id);
    void listAll();
    const std::vector<Student>& getAll() const { return students; }
};


#endif  // DATABASE_H