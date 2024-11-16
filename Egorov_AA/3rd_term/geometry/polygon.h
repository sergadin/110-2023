#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include "Point.h"
#include "Line.h"

class Polygon {
private:
    std::vector<Point> vertices; // Вершины многоугольника

public:
    Polygon(const std::vector<Point>& vertices);

    // Получение сечения многоугольника с прямой
    Polygon intersect(const Line& line) const;

    // Отрисовка
    void draw() const;
};

#endif // POLYGON_H

