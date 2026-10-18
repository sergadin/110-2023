#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include <vector>
#include "Point.h"
#include <stdexcept>

class ConvexHull {
public:
    ConvexHull();

    void addPoint(const Point& point);

    std::vector<Point> buildHull();

     static double getPerimeter(const std::vector<Point>& hull);

private:
    std::vector<Point> findLowerHull(const std::vector<Point>& points);
    std::vector<Point> findUpperHull(const std::vector<Point>& points);
    void removeDuplicates(std::vector<Point>& points);

    std::vector<Point> points;

};

#endif
