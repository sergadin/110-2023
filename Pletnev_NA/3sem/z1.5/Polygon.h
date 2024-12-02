#ifndef POLYGON_H
#define POLYGON_H
#include "Point.h"

bool isEmpty(const std::vector<Point>& Polygon);
bool isConvex(const std::vector<Point>& Polygon);

class Polygon 
{
private:
    std::vector<Point> vertices_;
public:
    Polygon(const std::vector<Point>& vertices) : vertices_(vertices) 
    {
        if (isEmpty(vertices_)) {
            throw Error(-10, "Polygon cannot be empty\n");
        }
        if (vertices_.size() < 3) {
            throw Error(-12, "Polygon must have min 3 peaks\n");
        }
        if (!isConvex(vertices_)) {
            throw Error(-11, "Polygon must be convex\n");
        }
    }
    int get_n() const;
    const Point& getPoint_i(int i) const;
};

#endif