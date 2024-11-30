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
    
    //Point p1, p2;
    std::vector<Point> polyPoints;
    std::string stroke;
    
 //  for (int i = 0; i < 2; i++	) {
 //       std::getline(input, stroke);
  //      std::istringstream iss(stroke);
 //       double x, y;
 //       if (iss >> x >> y) {
 //          linePoints.emplace_back(x, y);
  //      }
  //      else {
  //          std::cerr << "Invalid format: " << stroke << std::endl;
  //      }
  //  }

    while (std::getline(input, stroke)) {
        std::istringstream iss(stroke);
        double x, y;
        if (iss >> x >> y) {
            polyPoints.emplace_back(x, y);
        }
        else {
            std::cerr << "Invalid format: " << stroke << std::endl;
        }
    }
    
    Line line(1, 0, -2);    

    Polygon polygon(polyPoints);
    
    auto [leftPolygon, rightPolygon] = polygon.split(line);
        
    Polygon(leftPolygon).print("output1.txt");
    Polygon(rightPolygon).print("output2.txt");

    input.close();
    return 0;
}catch( ... ){

}
return 0;
}
