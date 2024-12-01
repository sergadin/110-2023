#pragma once

#include <vector> 

class Point  {

private:
  double mX;
  double mY;

public:
  Point(double x,double y) : mX(x), mY(y) {}

  double GetX(void) const { 
    return mX; 
  };

  double GetY(void) const { 
    return mY; 
  };

};

class Triangulate {

private:
  static bool isConvex(const std::vector<Point> &contour, int u, int v, int w, int n, int *V);

public:

  // triangulate a polygon using ear-clipping algorithm
  static bool makeTriangulation(const std::vector<Point> &polygon,
                      std::vector<Point> &result);

  // compute area of a polygon
  static double compute_area(const std::vector<Point> &polygon);

  // check if point is inside a triangle
  static bool InsideTriangle(double Ax, double Ay,
                      double Bx, double By,
                      double Cx, double Cy,
                      double Px, double Py);

  // draw polygon using gnuplot
  static void plotPolygon(const std::vector<Point> &contour);

};



