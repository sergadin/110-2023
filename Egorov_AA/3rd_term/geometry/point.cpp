#include "point.h"

// Конструктор
Point::Point(double x, double y) : x(x), y(y) {}

// Получение координат
double Point::getX() const { return x; }
double Point::getY() const { return y; }

// Перегрузка операторов
Point Point::operator+(const Point& other) const {
    return Point(x + other.x, y + other.y);
}

Point Point::operator-(const Point& other) const {
    return Point(x - other.x, y - other.y);
}

bool Point::operator==(const Point& other) const {
    if ((fabs(x - other.x) > 1e-6) || (fabs(y - other.y) > 1e-6)){
        return false;
    }
    return true;
}

// Отрисовка (для gnuplot можно создать файл с координатами)
void Point::draw() const {
    std::cout << x << " " << y << std::endl;
}
