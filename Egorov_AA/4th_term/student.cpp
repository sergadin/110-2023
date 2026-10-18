#include "student.h"
#include <iostream>

void Student::print() const {
    std::cout << "ID: " << id
        << ", Name: " << name
        << ", Group: " << group
        << ", GPA: " << gpa
        << ", Info: " << info << "\n";
}
