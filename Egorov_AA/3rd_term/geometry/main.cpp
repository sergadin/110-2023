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
        	
    std::vector<Point> points;
    std::string stroke;
    
    while (std::getline(input, stroke)) {
       std::istringstream iss(stroke);
       double x, y;
       if (iss >> x >> y) {
           points.emplace_back(x, y);
       }
       else {
           std::cerr << "Invalid format: " << stroke << std::endl;
       }
    }

    Polygon polygon(points);
    
    Line line(1, 0, -2);    
    
    auto [leftPolygon, rightPolygon] = polygon.split(line);
        
    Polygon(leftPolygon).print("output1.txt");
    Polygon(rightPolygon).print("output2.txt");

    input.close();
    return 0;
}catch( ... ){

}
return 0;
}
