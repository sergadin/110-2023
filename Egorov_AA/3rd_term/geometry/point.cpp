#include "point.h"
#include <iostream>
#include <cmath>

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
    if ((std::fabs(x - other.x) > 1e-6) || (std::fabs(y - other.y) > 1e-6)) {
        return false;
    }
    return true;
}

bool Point::operator<(const Point& other) const {
    if (x != other.x)
        return x < other.x;
    return y < other.y;
}

void Point::draw() const {
    std::cout << x << " " << y << std::endl;
}
