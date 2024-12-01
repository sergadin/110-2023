#include <iostream>
#include <fstream>
#include "polygon.h"
#include "point.h"


const std::vector<Point>& Polygon::getVertices() const {
    return vertices;
}

std::pair<std::vector<Point>, std::vector<Point>> Polygon::split(const Line& line) const {
    std::vector<Point> left, right;

    for (size_t i = 0; i < vertices.size(); ++i) {
        Point current = vertices[i];
        Point next = vertices[(i + 1) % vertices.size()];

        int currentSide = line.side(current);
        int nextSide = line.side(next);

        // добавляем текущую вершину в соответствующую часть
        if (currentSide >= 0) left.push_back(current);
        if (currentSide <= 0) right.push_back(current);

        // если ребро пересекает прямую, добавляем точку пересечения
        Point intersectionPoint;
        if (currentSide * nextSide < 0 && 
            line.intersection(current, next, intersectionPoint)) {
            left.push_back(intersectionPoint);
            right.push_back(intersectionPoint);
        }
    }

    return {left, right};
}

void Polygon::print(const std::string& filename) const {
    std::ofstream output(filename);
    if (!output.is_open()) {
        std::cerr << "Unable to open output file" << std::endl;
        return;
    }
    
    for (const auto& vertex : vertices) {
        output << vertex.getX() << " " << vertex.getY() << std::endl;
    }
    
    output.close();
}
