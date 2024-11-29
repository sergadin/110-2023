#include <iostream>
#include <vector>
#include "polygon.h"
#include "point.h"
#include "line.h"

int main() {
    std::vector<Point> points = {Point(0,0), Point(0,4), Point(4,4), Point(4,0)};
    Polygon polygon({{0, 0}, {4, 0}, {4, 4}, {0,4}, {0,0}});
    Line line(0, 1, -3);
    std::vector<Polygon> result = polygon.splitByLine(line);

    for (const auto& poly : result) {
        poly.print();
    }


    return 0;
}
