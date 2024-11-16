#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <math.h>

class Point {
private:
    double x;
    double y;

public:
    // Конструктор
    Point(double x = 0.0, double y = 0.0);

    // Получение координат
    double getX() const;
    double getY() const;

    // Перегрузка операторов
    Point operator+(const Point& other) const;
    Point operator-(const Point& other) const;
    bool operator==(const Point& other) const;

    // Отрисовка точки (можно использовать для gnuplot)
    void draw() const;
};

#endif // POINT_H
