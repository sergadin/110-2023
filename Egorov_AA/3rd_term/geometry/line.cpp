#include <cmath>
#include <iostream>
#include "line.h"

Line::Line(double a, double b, double c) : a(a), b(b), c(c) {}

Line::Line(const Point& p1, const Point& p2) {
    a = p2.getY() - p1.getY();
    b = p1.getX() - p2.getX();
    c = -(a * p1.getX() + b * p1.getY());
}

bool Line::intersection(const Point& p1, const Point& p2, Point& intersection) const {
    double x1 = p1.getX(), y1 = p1.getY(),
        x2 = p2.getX(), y2 = p2.getY(),
        xi, yi;
    double denominator = a * (x2 - x1) + b * (y2 - y1);
    if (std::abs(denominator) < 1e-9) {
        if(std::abs(a*x1 + b*y1 + c < 1e-9 && std::abs(a*x2 + b*y2 +c) < 1e-9)){
            return false;
        }
        return false;
    }

    double t = -(a * x1 + b * y1 + c) / denominator;
    if (t < 0 || t > 1) 
        return false;

    xi = x1 + t * (x2 - x1);
    yi = y1 + t * (y2 - y1);
    
    intersection.setX(xi);
    intersection.setY(yi);

    // проверяем, лежит ли точка на отрезке
    if (std::fmin(x1, x2) - 1e-9 <= xi && xi <= std::fmax(x1, x2) + 1e-9 &&
        std::fmin(y1, y2) - 1e-9 <= yi && yi <= std::fmax(y1, y2) + 1e-9) {
        return true;
    }

    return false;
}

int Line::side(const Point& p) const {
    double value = a * p.getX() + b * p.getY() + c;
    if (value > 0) return 1;
    if (value < 0) return -1;
    return 0;
}

void Line::draw() const {
    std::cout << a << "x + " << b << "y + " << c << std::endl;
}
