#include "Point.h"

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
    return x == other.x && y == other.y;
}

// Отрисовка (для gnuplot можно создать файл с координатами)
void Point::draw() const {
    std::cout << x << " " << y << std::endl;
}
