#include <iostream>
#include <cmath>
#include "point.h"

Point::Point() : x(0), y(0) {}
Point::Point(double x, double y) : x(x), y(y) {}

double Point::getX() const { return x; }
double Point::getY() const { return y; }

void Point::setX(double x_value) { x = x_value; }
void Point::setY(double y_value) { y = y_value; }


Point Point::operator+(const Point& other) const {
    return Point(x + other.x, y + other.y);
}

Point Point::operator-(const Point& other) const {
    return Point(x - other.x, y - other.y);
}

bool Point::operator==(const Point& other) const {
    if ((std::fabs(x - other.x) > 1e-9) || (std::fabs(y - other.y) > 1e-9)) {
        return false;
    }
    return true;
}

bool Point::operator<(const Point& other) const {
    if (std::abs(x - other.x) > 1e-9)
        return x < other.x;
    return y < other.y;
}
