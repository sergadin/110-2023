#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "ConvexHull.h"


int main(void) {
    double perimeter;
    srand(time(0));



    for (int numPoints = 3; numPoints <= 10000; numPoints *= 10) {
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
        perimeter = ConvexHull::getPerimeter(hullPoints);

        std::cout << "Number of points: " << numPoints << ", Perimeter: " << perimeter << std::endl;



        //std::cout << "Convex Hull Points:" << std::endl;
        //for (const auto& p : hullPoints) {
        //    std::cout << p << std::endl;
       // }
    }

    return 0;
}
