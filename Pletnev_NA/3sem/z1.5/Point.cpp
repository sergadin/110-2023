#include "Point.h"

#define eps 1e-6 

double Point:: get_x() const
{
    return x_;
};

double Point:: get_y() const
{
    return y_;
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

    //std::cout << "p.x = " << p.get_x() << " p.y = " << p.get_y() << std::endl;
    //std::cout << "a.x = " << a.get_x() << " a.y = " << a.get_y() << std::endl;
    //std::cout << "b.x = " << b.get_x() << " b.y = " << b.get_y() << std::endl;

    Point ap(p.get_x() - a.get_x(), p.get_y() - a.get_y());
    //std::cout << "ap.x = " << ap.get_x() << " ap.y = " << ap.get_y() << std::endl;

    Point ab(b.get_x() - a.get_x(), b.get_y() - a.get_y());
    //std::cout << "ab.x = " << ab.get_x() << " ab.y = " << ab.get_y() << std::endl;

    double dot_ab_ab = dot_product(ab, ab);
    //std::cout << "dot_ab_ab = " << dot_ab_ab << std::endl;
    if (dot_ab_ab < eps) return pointToPointDist(p, a); // отрезок вырожден в точку

    double t = dot_product(ap, ab) / dot_ab_ab;
    //std::cout << "t = " << t << std::endl;
    t = std::max(0.0, std::min(1.0, t));
    //std::cout << "tp = " << t << std::endl;

    Point C(0, 0);
    C.set_x(a.get_x() + t * ab.get_x());
    C.set_y(a.get_y() + t * ab.get_y());

    //std::cout << "c.x = " << C.get_x() << " c.y = " << C.get_y() << std::endl;

    double r = pointToPointDist(p, C);
    //std::cout << "r = " << r << "\n" << std::endl;

    return r;
}

bool intersect(const Point &a,const Point &b,const Point &c,const Point &d)
{
    double cp1 = cross_product(a, b, c);
    double cp2 = cross_product(a, b, d);
    double cp3 = cross_product(c, d, a);
    double cp4 = cross_product(c, d, b);

    // Проверка на коллинеарность
    if (std::abs(cp1) < 1e-9 && std::abs(cp2) < 1e-9) 
    {
        // отрезки коллинеарны, проверка на перекрытие
        return  std::min(a.get_x(), b.get_x()) <= std::max(c.get_x(), d.get_x()) &&
                std::max(a.get_x(), b.get_x()) >= std::min(c.get_x(), d.get_x()) &&
                std::min(a.get_y(), b.get_y()) <= std::max(c.get_y(), d.get_y()) &&
                std::max(a.get_y(), b.get_y()) >= std::min(c.get_y(), d.get_y());
    }

    return ((cp1 > 0 && cp2 < 0) || (cp1 < 0 && cp2 > 0)) &&
            ((cp3 > 0 && cp4 < 0) || (cp3 < 0 && cp4 > 0));

}
double segmentDistance(const Point& a, const Point& b, const Point& c, const Point& d) 
{
    
    if (intersect(a, b, c, d))
    {
        return 0;
    }

    return std::min({pointToSegmentDist(a, c, d),
                     pointToSegmentDist(b, c, d),
                     pointToSegmentDist(c, a, b),
                     pointToSegmentDist(d, a, b)});
}
