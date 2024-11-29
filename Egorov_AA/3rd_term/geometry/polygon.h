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

    const std::vector<Point>& getVertices() const;

    std::vector<Polygon> splitByLine(const Line& line) const;

    void print() const;
};

#endif // POLYGON_H
