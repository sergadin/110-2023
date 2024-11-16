#include "Point.h"
#include <cmath>

Point::Point() : x(0), y(0) {}

Point::Point(double x, double y) : x(x), y(y) {}


bool Point::operator<(const Point& other) const {
    double eps = 0.00001;
    if (x < other.x) {
        return true;
    } else if (labs(x - other.x) <eps && y < other.y) {
        return true;
    }
    return false;
}

bool Point::operator>(const Point& other) const {
    double eps = 0.00001;
    return !(*this < other) && (labs(*this > other)<eps);
}

void Point::print() const {
    std::cout << "(" << x << ", " << y << ")";
}

int Point::orientation(const Point& p, const Point& q, const Point& r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    double eps = 0.00001;

    if (labs(val) < eps) {
        return 0;
    } else if (val > 0) {
        return 1;
    } else {
        return 2;
    }
}
