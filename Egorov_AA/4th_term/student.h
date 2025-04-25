#ifndef STUDENTS_H
#define STUDENTS_H

#include <string>

struct Student {  // Добавить структуру ФИО
    int id;
    std::string name;
    int group;
    double gpa;
    std::string info;

    void print() const;
};

#endif  // STUDENTS_H