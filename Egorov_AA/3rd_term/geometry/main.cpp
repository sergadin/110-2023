#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "polygon.h"
#include "point.h"
#include "line.h"

int main() {
try {
    std::ifstream input("input.txt");
    if (!input.is_open()) {
        std::cerr << "Unable to open input file" << std::endl;
        return 1;
    }
    
    int verticesNum;
    std::vector<Point> linePoints;
    std::vector<Point> polyPoints;
    std::string stroke;

    input >> verticesNum;

    std::cout << verticesNum << std::endl;

    std::getline(input, stroke);

    for (int i = 0; i < verticesNum + 1; i++) {
        std::getline(input, stroke);
        std::istringstream iss(stroke);
        double x, y;
        if (iss >> x >> y) {
            polyPoints.emplace_back(x, y);
        }
        else {
            std::cerr << "Invalid format: " << stroke << std::endl;
        }

        polyPoints[i].draw();
    }

    std::getline(input, stroke);
    std::istringstream iss(stroke);
    double a, b, c;
    iss >> a >> b >> c;
    Line line(a, b, c);

    line.draw();

    Polygon polygon(polyPoints);
    
    std::pair<std::vector<Point>, std::vector<Point>> pairOfPolygons = polygon.split(line);

    Polygon(polygon).print("output.txt");
    Polygon(pairOfPolygons.first).print("output1.txt");
    Polygon(pairOfPolygons.second).print("output2.txt");

    input.close();
    return 0;
}catch( ... ){

}
return 0;
}
