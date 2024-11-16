#include "line.h"
#include <stdexcept>
#include <math.h>

Line::Line(double a, double b, double c) : a(a), b(b), c(c) {}

Line::Line(const Point& p1, const Point& p2) {
    a = p2.getY() - p1.getY();
    b = p1.getX() - p2.getX();
    c = a * p1.getX() + b * p1.getY();
}

bool Line::intersects(const Line& other) const {
    if ((fabs(a * other.b - b * other.a) - 0) > 1e-10) {
        return true;
    }
    return false;
}

Point Line::intersection(const Line& other) const {
    double det = a * other.b - b * other.a;
    if (fabs(det - 0) > 1e-10) throw std::runtime_error("Линии не пересекаются.");
    double x = (b * other.c - c * other.b) / det;
    double y = (c * other.a - a * other.c) / det;
    return Point(x, y);
}

void Line::draw() const {
    // Можно выводить уравнение линии
    std::cout << a << "x + " << b << "y + " << c << " = 0" << std::endl;
}
