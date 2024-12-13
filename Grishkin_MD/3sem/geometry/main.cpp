#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "ConvexHull.h"
#include <iomanip>
#include <limits>

int main(void) {
    srand(time(0));

    for (int numPoints = 100; numPoints <= 1000000; numPoints *= 10) {
        ConvexHull hull;
        for (int i = 0; i < numPoints; ++i) {
            double x = static_cast<double>(rand()) / RAND_MAX;
            double y = static_cast<double>(rand()) / RAND_MAX;

            try {
                hull.addPoint(Point(x, y));
            } catch (const std::out_of_range& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                return 1;
            }
        }

        std::vector<Point> hullPoints = hull.buildHull();
        double perimeter = ConvexHull::getPerimeter(hullPoints);

        std::cout << "Number of points: " << numPoints << ", Perimeter: " << perimeter << std::endl;
    }

    // Тест с заранее заданными точками
    std::cout << "\nTest with predefined points:\n";
    ConvexHull fixedHull;

    std::vector<Point> predefinedPoints = {
        Point(0.1, 0.1),
        Point(0.9, 0.1),
        Point(0.9, 0.9),
        Point(0.1, 0.9),
        Point(0.5, 0.5),
        Point(0.2, 0.8),
        Point(0.8, 0.2)
    };

    for (const auto& p : predefinedPoints) {
        fixedHull.addPoint(p);
    }

    std::vector<Point> fixedHullPoints = fixedHull.buildHull();
    double fixedPerimeter = ConvexHull::getPerimeter(fixedHullPoints);

    std::cout << "Number of predefined points: " << predefinedPoints.size()
              << ", Perimeter: " << fixedPerimeter << std::endl;

    std::cout << "Convex Hull Points for predefined points:" << std::endl;
    for (const auto& point : fixedHullPoints) {
        std::cout << "(" << point.x << ", " << point.y << ")" << std::endl; //
    }

    return 0;
}

