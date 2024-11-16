#include "polygon.h"

Polygon::Polygon(const std::vector<Point>& vertices) : vertices(vertices) {}

Polygon Polygon::intersect(const Line& line) const {
    // Логика для нахождения точек пересечения
    // Возвращаем новый многоугольник, образованный от сечения
    std::vector<Point> intersection_points;
    // TODO: Реализовать алгоритм нахождения сечения
    return Polygon(intersection_points);
}

void Polygon::draw() const {
    for (const auto& point : vertices) {
        point.draw();
    }
}
