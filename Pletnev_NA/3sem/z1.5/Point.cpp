#include "Point.h"

#define eps 1e-6 

double Point:: get_x() const
{
    return x_;
};

double Point:: get_y() const
{
    return x_;
};

void Point:: set_x(double x)
{
    x_ = x;
};

void Point:: set_y(double y)
{
    y_ = y;
};


Point& Point::operator=(const Point& other) 
{
    if (this != &other) 
    { // Проверка на самоприсваивание
        x_ = other.x_;
        y_ = other.y_;
    }
    return *this; // Возвращаем ссылку на текущий объект
};

bool Point::operator<(const Point& other) const 
{
    if (this->x_ < other.x_) return true;
    if (this->x_ > other.x_) return false;
    return this->y_< other.y_;
}

// Скалярное произведение
double dot_product(const Point& a, const Point& b) 
{
    return a.get_x() * b.get_x() + a.get_y() * b.get_y();
}

// Расстояние между двумя точками
double pointToPointDist(const Point& a, const Point& b) 
{
    double dx = a.get_x() - b.get_x();
    double dy = a.get_y() - b.get_y();
    return std::sqrt(dx * dx  + dy * dy);
}

// Векторное произведение (для проверки пересечения)
double cross_product(const Point& a, const Point& b, const Point& c) 
{
    return (b.get_x() - a.get_x()) * (c.get_y() - a.get_y()) - (b.get_y() - a.get_y()) * (c.get_x() - a.get_x());
}

//Расстояние от точки до отрезка
double pointToSegmentDist(const Point& p, const Point& a, const Point& b) 
{

    Point ap(p.get_x() - a.get_x(), p.get_y() - a.get_y());
    Point ab(b.get_x() - a.get_x(), b.get_y() - a.get_y());

    double dot_ab_ab = dot_product(ab, ab);
    if (dot_ab_ab < eps) return pointToPointDist(p, a); // отрезок вырожден в точку

    double t = dot_product(ap, ab) / dot_ab_ab;
    t = std::max(0.0, std::min(1.0, t));

    Point с(a.get_x() + t * ab.get_x(), a.get_y() + t * ab.get_y());

    return pointToPointDist(p, с);
}


double segmentDistance(const Point& a, const Point& b, const Point& c, const Point& d) 
{
    return std::min({pointToSegmentDist(a, c, d),
                     pointToSegmentDist(b, c, d),
                     pointToSegmentDist(c, a, b),
                     pointToSegmentDist(d, a, b)});
}
