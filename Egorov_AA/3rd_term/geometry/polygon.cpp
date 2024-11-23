#include <iostream>
#include <map>
#include <vector>
#include <deque>
#include "polygon.h"


const std::vector<Point>& Polygon::getVertices() const {
    return vertices;
}

std::vector<Polygon> Polygon::splitByLine(const Line& line) const {
    std::vector<Point> intersectionPoints;
    std::vector<std::vector<Point>> polygons;
    std::vector<Point> currentPolygon;
    bool sideOnLine = false;

    for (size_t i = 0; i < vertices.size(); ++i) {
        Point p1 = vertices[i];
        Point p2 = vertices[(i + 1) % vertices.size()];
        currentPolygon.push_back(p1);

        Point intersection;
        if (line.intersectSegment(p1, p2, intersection)) {
            if (intersectionPoints.empty() || !(intersection == intersectionPoints.back())){
                intersectionPoints.push_back(intersection);
            }
            currentPolygon.push_back(intersection);
            polygons.push_back(currentPolygon);
            currentPolygon.clear();
            currentPolygon.push_back(intersection);
        }
        else if (std::abs(line.a * p1.getX() + line.b * p1.getY() + line.c) < 1e-9 &&
                 std::abs(line.a * p2.getX() + line.b * p2.getY() + line.c) < 1e-9) {
                sideOnLine = true;
            }
    }

    // добавляем последний многоугольник
    if (!currentPolygon.empty()) {
        currentPolygon.push_back(currentPolygon.front());
        polygons.push_back(currentPolygon);
    }

    // Если прямая совпадает с одной из сторон, возвращаем две части
        if (sideOnLine) {
            std::vector<Point> upper, lower;
            for (const auto& p : vertices) {
                if (line.a * p.getX() + line.b * p.getY() + line.c > 0) {
                    upper.push_back(p);
                } else if (line.a * p.getX() + line.b * p.getY() + line.c < 0) {
                    lower.push_back(p);
                }
            }
            if (!upper.empty()) polygons.push_back(upper);
            if (!lower.empty()) polygons.push_back(lower);
        }



    // формируем результат
    std::vector<Polygon> result;
    for (const auto& poly : polygons) {
        std::vector<Point> uniquePoly;
        for (const auto& point: poly){
            if (uniquePoly.empty() || !(point == uniquePoly.back())){
                uniquePoly.push_back(point);
            }
        }
        if (uniquePoly.size() >= 3){
            result.emplace_back(uniquePoly);
        }
    }

    return result;
}

void Polygon::print() const {
    for (const auto& vertex : vertices) {
        std::cout << "(" << vertex.getX() << ", " << vertex.getY() << ") ";
    }
    std::cout << std::endl;
}
