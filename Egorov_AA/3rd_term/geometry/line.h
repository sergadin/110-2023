#ifndef LINE_H
#define LINE_H

#include "point.h"

class Line {
public:
    double a, b, c; // ax + by + c = 0
    
    // конструкторы
    Line(double a, double b, double c);
    Line(const Point& p1, const Point& p2);

    // поиск пересечения полигона прямой
    bool intersection(const Point& p1, const Point& p2, Point& intersection) const;
    
    // ориентация точки относительно прямой
    int side(const Point& p) const;

    void draw() const;
};

#endif // LINE_H
