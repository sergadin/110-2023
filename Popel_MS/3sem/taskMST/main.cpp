#include "mst.h"
#include "geom_obj.h"
#include <iostream>
#include <fstream>
using namespace std;
int Point::num_ = 0;
int main(void){
  vector<Point> points = {{3,2},{2,6},{9,1}, {14,6}, {8,4}, {6,6}, {11, 8}, {7,9}, {4,11},{12,3}};
  //vector<Point> points = {{1,1}, {5,2}, {7,3}, {3,5}};
  //Point pnt(2,2);
  for(int i = 0; i < points.size(); i++){
    std::cout << "( " << points[i].getX() << ", " << points[i].getY() << ") id: " << points[i].getId() << std::endl;
  }
  printf("%ld - first\n", points.size());
  vector<Edge> res = Mst(points);
  plotMst(res, points);
  //addPoint(points, pnt);
  /*for(int i = 0; i<pnts.size();i++){
    std::cout << pnts[i].getX() << " " << pnts[i].getY() << " " << pnts[i].getId() <<std::endl;
  }*/
  //printf("%ld - second\n", points.size());
  //std::vector<Edge> res2 = Mst(points);
  //plotMst(res2, points);
  
  return 0;
}
