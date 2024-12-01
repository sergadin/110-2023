#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include "point.h"
#include "line.h"

class Polygon {
private:
    std::vector<Point> vertices;

public:
    // конструктор
    Polygon(const std::vector<Point>& vertices) : vertices(vertices) {}
    
    // геттер
    const std::vector<Point>& getVertices() const;

    // разрезание многоугольника
    std::pair<std::vector<Point>, std::vector<Point>> split(const Line& line) const;
    
    // отрисовка многоугольника
    void print(const std::string& filename) const;
};

#endif // POLYGON_H
