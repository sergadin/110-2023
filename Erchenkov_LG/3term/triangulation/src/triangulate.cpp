#include <fstream>
#include "triangulate.hpp"

static const double eps = 1e-9;

double Triangulate::compute_area(const std::vector<Point> &polygon) {

  int sz = polygon.size();
  double res_area = 0.0;

  for (int p = sz - 1,q = 0; q < sz; p = q++) {
    res_area += polygon[p].GetX() * polygon[q].GetY() - polygon[q].GetX() * polygon[p].GetY();
  }

  return res_area * 0.5;
}

bool Triangulate::InsideTriangle(
                double Ax, double Ay,
                double Bx, double By,
                double Cx, double Cy,
                double Px, double Py
                ) 
{
  double ax, ay, bx, by, cx, cy, apx, apy, bpx, bpy, cpx, cpy;
  double cCROSSap, bCROSScp, aCROSSbp;

  ax = Cx - Bx;  ay = Cy - By;
  bx = Ax - Cx;  by = Ay - Cy;
  cx = Bx - Ax;  cy = By - Ay;
  apx= Px - Ax;  apy= Py - Ay;
  bpx= Px - Bx;  bpy= Py - By;
  cpx= Px - Cx;  cpy= Py - Cy;

  aCROSSbp = ax*bpy - ay*bpx;
  cCROSSap = cx*apy - cy*apx;
  bCROSScp = bx*cpy - by*cpx;

  return ((aCROSSbp >= 0.0) && (bCROSScp >= 0.0) && (cCROSSap >= 0.0));
};

bool Triangulate::isConvex(const std::vector<Point> &polygon, int prev, int cur, int next, int n,int *V) {
  int p;
  double Ax, Ay, Bx, By, Cx, Cy, Px, Py;

  Ax = polygon[V[prev]].GetX();
  Ay = polygon[V[prev]].GetY();

  Bx = polygon[V[cur]].GetX();
  By = polygon[V[cur]].GetY();

  Cx = polygon[V[next]].GetX();
  Cy = polygon[V[next]].GetY();

  if ((((Bx - Ax) * (Cy - Ay)) - ((By - Ay) * (Cx - Ax))) < eps) 
    return false;

  for (p = 0; p < n; p++)
  {
    if( (p == prev) || (p == cur) || (p == next) ) continue;
    Px = polygon[V[p]].GetX();
    Py = polygon[V[p]].GetY();
    if (InsideTriangle(Ax, Ay, Bx, By, Cx, Cy, Px, Py)) 
      return false;
  }

  return true;
}

bool Triangulate::makeTriangulation(const std::vector<Point> &polygon, std::vector<Point> &result) {
  int sz = polygon.size(); // amount of vertices
  if (sz < 3) 
    return false;

  int *V = new int[sz];


  // check that our polygon is counter-clockwise
  if (compute_area(polygon) > 0.0) 
    for (int v = 0; v < sz; v++) 
      V[v] = v;
  else
    for (int v = 0; v < sz; v++) 
      V[v] = (sz - 1) - v;

  int nv = sz;

  // removing nv - 2 verices and creating 1 triangle
  int count = 2 * nv; 

  for(int m = 0, v = nv - 1; nv > 2;) {
    if ((count--) <= 0) {
      return false;
    }

    int u = v; 
    if (nv <= u) u = 0;
    v = u + 1; 
    if (nv <= v) v = 0; 
    int w = v + 1; 
    if (nv <= w) w = 0; 

    if (isConvex(polygon, u, v, w, nv, V))
    {
      int a, b, c, s, t;

      a = V[u]; b = V[v]; c = V[w];

      result.push_back(polygon[a]);
      result.push_back(polygon[b]);
      result.push_back(polygon[c]);

      m++;

      // removing v from polygon
      for(s = v, t = v + 1;t < nv; s++, t++) 
        V[s] = V[t]; 
      nv--;

      count = 2*nv;
    }
  }

  delete[] V;

  return true;
}

void Triangulate::plotPolygon(const std::vector<Point> &result) {
  std::ofstream out;
  int sz = result.size() / 3;
  out.open("output.txt");

  if (!out) {
    out.close();
    throw -1;
  }

  for (int i = 0; i < sz; i++) {
    const Point &p1 = result[i * 3 + 0];
    const Point &p2 = result[i * 3 + 1];
    const Point &p3 = result[i * 3 + 2];
    out << p1.GetX() << " " << p1.GetY() << std::endl;
    out << p3.GetX() << " " << p3.GetY() << std::endl;
    out << p2.GetX() << " " << p2.GetY() << std::endl;
    out << p1.GetX() << " " << p1.GetY() << std::endl;
    out << p3.GetX() << " " << p3.GetY() << std::endl;
  }
  system("gnuplot -e \"plot 'output.txt' using 1:2 with lines\" -p");
  out.close();

}


