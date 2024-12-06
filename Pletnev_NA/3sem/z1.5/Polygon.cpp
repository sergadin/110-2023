#include "Polygon.h"

// Проверка на пустоту
bool isEmpty(const std::vector<Point>& Polygon) 
{
    return Polygon.size() < 1;
};

// Проверка на выпуклость
bool isConvex(const std::vector<Point>& Polygon) 
{
    if (Polygon.size() < 3) return true; //Отрезок или точка - выпуклы

    int n = Polygon.size();
    bool is_p = false;
    bool is_n = false;

    for (int i = 0; i < n; ++i) 
    {
        Point A = Polygon[(i + 1) % n];
        Point B = Polygon[i];
        Point C = Polygon[(i + 2) % n];
        double val = (A.get_x() - B.get_x()) * (C.get_y() - A.get_y()) -
                     (A.get_y() - B.get_y()) * (C.get_x() - A.get_x());

        if (val > 0) is_p = true;
        if (val < 0) is_n = true;

        if (is_p && is_n) return false;
    }
    return true;
};

int Polygon::get_n() const
{
    return vertices_.size();
}

const Point& Polygon::getPoint_i(int i) const
{
    return vertices_[i];
}