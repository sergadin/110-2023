#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include <vector>
#include "Point.h"

class ConvexHull {
public:
    ConvexHull();

    void addPoint(const Point& point);

    std::vector<Point> buildHull();

private:
    std::vector<Point> findLowerHull(const std::vector<Point>& points);
    std::vector<Point> findUpperHull(const std::vector<Point>& points);
    void removeDuplicates(std::vector<Point>& points);

    std::vector<Point> points;
};

#endif 
