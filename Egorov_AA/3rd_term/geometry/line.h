#ifndef LINE_H
#define LINE_H

#include "Point.h"

class Line {
private:
    double a, b, c; // Коэффициенты уравнения прямой ax + by + c = 0

public:
    Line(double a, double b, double c);
    Line(const Point& p1, const Point& p2);

    // Проверка, пересекается ли прямая с другой
    bool intersects(const Line& other) const;

    // Получение точки пересечения
    Point intersection(const Line& other) const;

    // Отрисовка линии для gnuplot
    void draw() const;
};

#endif // LINE_H
