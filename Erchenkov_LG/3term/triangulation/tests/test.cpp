#include <iostream>
#include <fstream>
#include "../src/triangulate.hpp"

int main(void) {

  //std::ifstream in;

  //in.open("input.txt");


  std::ofstream out;
  out.open("output.txt");
  if (!out) {
    std::cout << "Error: cannot open file to write" << std::endl;
    return -1;
  }
  
  // TEST 1
  /*
  std::vector<Point> data = {
    Point(1, 1), Point(1, 3), Point (4, 3), Point(4, 1)
  };
  */

  // TEST 2
  /*
  std::vector<Point> data = {
    Point(0, 0), Point(5, 6), Point(8, 3),
    Point(4, 2), Point(6, 1),
    };
  */

  // TEST 3
  /*
  std::vector<Point> data = {
    Point(0,0), Point(5, 6), Point(8, 3),
    Point(4, 2), Point(9, 2), Point(6, 1),
  };
  */

  // TEST 4
  /*
  std::vector<Point> data = {
    Point(0, 5), Point(3, 0), Point(3, 6),
    Point(5, 8), Point(1, 8), Point(2, 5),
  };
  */

  std::vector<Point> data = {
    Point(1, 1), Point(1, 5), Point(4, 5),
    Point(4, 7), Point(1, 7), Point(1, 9),
    Point(10, 9), Point(6, 7), Point(6, 2),
  };

 
  int input_sz = data.size();
  std::cout << "-------------" << "INPUT DATA" << "-------------" << std::endl;
  for (int i = 0; i < input_sz; i++) {
    std::cout << "Point " << i + 1 << ": " << "(" << data[i].GetX() << " " << data[i].GetY() << ")" << std::endl; 
  }

  std::vector<Point> result;

  Triangulate::makeTriangulation(data, result);


  int out_sz = result.size()/3;

  std::cout << "------------- " << "OUTPUT DATA" << " -------------" << std::endl;
  for (int i = 0; i < out_sz; i++) {
    const Point &p1 = result[i * 3 + 0];
    const Point &p2 = result[i * 3 + 1];
    const Point &p3 = result[i * 3 + 2];
    out << p1.GetX() << " " << p1.GetY() << " " << p2.GetX() << " " << p2.GetY() << " " << p3.GetX() << " " << p3.GetY() << std::endl;
    std::cout << "Triangle " << i + 1 << ": " << "(" << p1.GetX() << " " << p1.GetY() << ")" << " " << 
      "(" << p2.GetX() << " " << p2.GetY() << ")" << " " << 
      "(" << p3.GetX() << " " << p3.GetY() << ")" << std::endl;
  }


  Triangulate::plotPolygon(result);
  return 0;
  out.close();

}
