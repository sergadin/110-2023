#include <iostream>
#include <map>
#include <set>
#include <deque>
#include "polygon.h"


const std::vector<Point>& Polygon::getVertices() const {
    return vertices;
}

std::vector<Polygon> Polygon::splitByLine(const Line& line) const {
    std::vector<Point> intersectionPoints;
    std::vector<std::vector<Point>> polygons;
    std::vector<Point> currentPolygon;

    for (size_t i = 0; i < vertices.size(); ++i) {
        Point p1 = vertices[i];
        Point p2 = vertices[(i + 1) % vertices.size()];
        currentPolygon.push_back(p1);

        Point intersection;
        if (line.intersectSegment(p1, p2, intersection)) {
            intersectionPoints.push_back(intersection);
            currentPolygon.push_back(intersection);

            // закрываем текущий многоугольник
            if (!currentPolygon.empty()) {
                polygons.push_back(currentPolygon);
                currentPolygon.clear();
                currentPolygon.push_back(intersection); // начало нового многоугольника
            }
        }
    }

    // добавляем последний многоугольник
    if (!currentPolygon.empty()) {
        polygons.push_back(currentPolygon);
    }

    // формируем результат
    std::vector<Polygon> result;
    for (const auto& poly : polygons) {
        result.emplace_back(poly);
    }

    return result;
}

void Polygon::print() const {
    for (const auto& vertex : vertices) {
        std::cout << "(" << vertex.getX() << ", " << vertex.getY() << ") ";
    }
    std::cout << std::endl;
}
