#ifndef LINE_H
#define LINE_H

#include "point.h"

class Line {
private:
    double a, b, c; // ax + by + c = 0

public:

    Line(double a, double b, double c);
    Line(const Point& p1, const Point& p2);

    bool intersectSegment(const Point& p1, const Point& p2, Point& intersection) const;
};

#endif // LINE_H
