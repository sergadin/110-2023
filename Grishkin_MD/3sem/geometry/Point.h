#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cmath>

class Point {
public:
    double x;
    double y;
    //double eps = 0.000001;

    bool operator!=(const Point& other) const {
        return !(this->x == other.x && this->y == other.y);
    }

    bool operator==(const Point& other) const {
           return (this->x == other.x   && this->y == other.y);
       }

    Point();

    Point(double x, double y);

    bool operator<(const Point& other) const;
    bool operator>(const Point& other) const;

    void print() const;

    static int orientation(const Point& p, const Point& q, const Point& r);

     double distanceTo(const Point& other) const {
        return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
    }
};

#endif
