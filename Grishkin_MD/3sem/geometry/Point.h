#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
public:
    double x;
    double y;

    bool operator!=(const Point& other) const {
        return !(this->x == other.x && this->y == other.y);
    }

    bool operator==(const Point& other) const {
           return (this->x == other.x && this->y == other.y);
       }

    Point();

    Point(double x, double y);

    bool operator<(const Point& other) const;
    bool operator>(const Point& other) const;

    void print() const;

    static int orientation(const Point& p, const Point& q, const Point& r);
};

#endif
