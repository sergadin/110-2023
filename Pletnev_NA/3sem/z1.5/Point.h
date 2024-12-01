#ifndef POINT_H
#define POINT_H

#include "Error.h"

class Point
{
private:
    double x_;
    double y_;
    
public:
    Point(double x = 0.0, double y = 0.0) : x_(x), y_(y) {}
    Point(const Point& other) : x_(other.x_), y_(other.y_) {}

    double get_x() const;
    double get_y() const;
    void set_x(double x);
    void set_y(double y);
    bool operator<(const Point& other) const;
    Point& operator=(const Point& other);

};

#endif