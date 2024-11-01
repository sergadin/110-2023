#include <iostream>
#include <vector>
#include "ConvexHull.h"

int main(void) {
    ConvexHull hull;

    hull.addPoint(Point(4, 1));
    hull.addPoint(Point(5, 3));
    hull.addPoint(Point(6, 1));
    hull.addPoint(Point(7, 3));
    hull.addPoint(Point(6, 4));
    hull.addPoint(Point(5, 5));
    hull.addPoint(Point(4, 4));
    hull.addPoint(Point(3, 3));
    //hull.addPoint(Point(-8, -3));
    //hull.addPoint(Point(-9, -4));

    std::vector<Point> hullPoints = hull.buildHull();

    std::cout << "Points of the convex hull: " << std::endl;
    for (const auto& point : hullPoints) {
        point.print();
        std::cout << std::endl;
    }

    return 0;
}
