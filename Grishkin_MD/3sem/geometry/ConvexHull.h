#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include <vector>
#include "Point.h"

class ConvexHull {
public:
    // Конструктор
    ConvexHull();

    // Добавление точки
    void addPoint(const Point& point);

    // Построение выпуклой оболочки
    std::vector<Point> buildHull();

private:
    // Вспомогательные методы
    std::vector<Point> findLowerHull(const std::vector<Point>& points);
    std::vector<Point> findUpperHull(const std::vector<Point>& points);
    void removeDuplicates(std::vector<Point>& points);

    // Хранилище точек
    std::vector<Point> points;
};

#endif // CONVEX_HULL_H
