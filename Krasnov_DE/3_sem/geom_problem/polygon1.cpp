#include "polygon1.h"

using namespace std;

double Get_length(const Point &p1,const Point &p2){
    double d_x = fabs(p1.x - p2.x);
    double d_y = fabs(p1.y - p2.y);
    return sqrt(d_x * d_x + d_y * d_y);

}

Triple& findMaxTriple(vector<Triple>& diagonals){
    int d_size = diagonals.size();
    Triple a = {0, 0, 0};
    for(int i =0 ; i != d_size; i++){
        for(int j =0 ; j != d_size; j++){
            if (diagonals[i].length < diagonals[j].length){
                a = diagonals[i];
                diagonals[i]= diagonals[j];
                diagonals[j] = a;
            }
        }
    }
    return diagonals.back();
}

Triple& findMinTriple(vector<Triple>& diagonals){
    int d_size = diagonals.size();
    Triple a = {0, 0, 0};
    for(int i =0 ; i != d_size; i++){
        for(int j =0 ; j != d_size; j++){
            if (diagonals[i].length > diagonals[j].length){
                a = diagonals[i];
                diagonals[i]= diagonals[j];
                diagonals[j] = a;
            }
        }
    }
    return diagonals.back();
}

Vector::Vector(double a_v, double b_v){
  a = a_v;
  b = b_v;
}

Vector::~Vector(){}

double Vector::Get_a(){
  return a;
}

double Vector::Get_b(){
  return b;
}

Vector::Vector (const Vector& v1){
  double eps = 1e-6;
  double a_v1 = v1.a;
  double b_v1 = v1.b;
  if(fabs(b_v1) > eps ){
    a = 1;
    b = (-1) * (a_v1 * a) / (b_v1);
  }
  else{
    a = 0;
    b = 1;
  }
}


Line::Line(double x, double y, double a_l, double b_l) : Vector(a_l, b_l){
  origin.x = x;
  origin.y = y;
}

Line::~Line(){}

Line::Line(const Line& other) : Vector(other.a, other.b), origin(other.origin){}

void Line::Print_Line() const{
  cout << "x= " <<origin.x << " + " << a << "*t " << endl;
  cout << "y= " <<origin.y << " + " << b << "*t " << endl;
}

Point Find_intersection(Line &line_1,Line &line_2){
    double denom;
    double t;
    double eps = 1e-6;
    denom = line_2.b * line_1.a - line_2.a * line_1.b ;
    if (fabs(denom) < eps){
        throw invalid_argument("intersect paralel lines");
    }
    t = (line_2.a * (line_1.origin.y - line_2.origin.y) + line_2.b * (line_2.origin.x - line_1.origin.x)) / denom;

    return {line_1.origin.x + line_1.a * t, line_1.origin.y + line_1.b * t};


}


Polygon::Polygon(unsigned size_p,const vector<Point>& points_p){
  points = points_p;
  size_polygon = size_p;
  if(size_p < 3){
    throw invalid_argument("is not polygon");
  }

  for(size_t i =0 ; i != size_p; i++){
    vectors.push_back(Vector(0,0));
  }
  for(size_t i=0; i!= size_p - 1 ; i++){
    auto vec = Vector(points_p[i+1].x - points_p[i].x, points_p[i+1].y - points_p[i].y);
    vectors[i] = vec;
  }

  vectors[size_p - 1] = Vector(points_p[0].x - points_p[size_p - 1].x, points_p[0].y - points_p[size_p - 1].y);
  cout << vectors[size_p - 1].a << " " << vectors[size_p - 1].b << endl;

}


Polygon::~Polygon(){}

void Polygon::Print_Polygon() const{
  for(size_t i = 0 ; i != size_polygon; i++){
    cout << points[i].x << " " << points[i].y << endl;
  }
}

double Polygon::Get_vectors_product(int i, int j) const{
  return (vectors[i].a * vectors[j].b - vectors[j].a * vectors[i].b);

}


bool Polygon::Bulge_check() const{
  for(size_t i = 0; i != size_polygon - 2; i++){
    if(Get_vectors_product(i, i + 1) * Get_vectors_product(i + 1, i + 2) <= 0){
      throw invalid_argument("polygon is not bulge1");
      return false;
    }
  }

  if(Get_vectors_product(size_polygon-2, size_polygon-1) * Get_vectors_product(size_polygon - 1, 0)  <= 0){
    throw invalid_argument("polygon is not bulge2");
    return false;
  }

  if(Get_vectors_product(size_polygon - 1, 0) * Get_vectors_product(0, 1)  <= 0){
    throw invalid_argument("polygon is not bulge3");
    return false;
  }

  return true;
}


pair<Triple, Vector> Polygon::Get_min_gap() const{
  vector<Point> centers (size_polygon);
  vector<Point> intersect (size_polygon);
  vector<Triple> length (size_polygon);
  vector<Line> lines;
  vector<Triple> res (size_polygon);
  for(size_t i =0; i != size_polygon - 1; i++){
    centers[i].x = (points[i].x + points[i + 1].x) / 2;
    centers[i].y = (points[i].y + points[i + 1].y) / 2;
  }

  centers[size_polygon - 1].x = (points[size_polygon - 1].x + points[0].x) / 2;
  centers[size_polygon - 1].y = (points[size_polygon - 1].y + points[0].y) / 2;
  for(size_t i = 0; i != size_polygon; i++){
    //    cout << centers[i].x << " " << centers[i].y << endl;
  }

  for(size_t i = 0; i != size_polygon; i++){
    lines.push_back(Line(0,0,0,0));
  }

  for(size_t j = 0 ; j != size_polygon; j++){
    for(size_t i = 0; i != size_polygon; i++){
      lines[i] = Line(points[i].x, points[i].y, vectors[j].a, vectors[j].b);
    }

    Vector perp{vectors[j]};
    lines[j]= Line(centers[j].x, centers[j].y, perp.a, perp.b);

    for(size_t i = 0; i != size_polygon; i++){
      if(i == j){
        intersect[i].x = centers[j].x;
        intersect[i].y = centers[j].y;
      }
      else{
        intersect[i].x = Find_intersection(lines[j], lines[i]).x;
        intersect[i].y = Find_intersection(lines[j], lines[i]).y;
      }

      length[i].length = Get_length(centers[j], intersect[i]);
      length[i].vertex1 = i;
      length[i].vertex2 = j;
    }
    res[j] = findMaxTriple(length);
  }

  auto result = findMinTriple(res);
        
  cout << "the height of the polygon = ";
  cout << result.length << endl;
  cout << "and passes through the vertex ";
  cout << points[result.vertex1].x << " " << points[result.vertex1].y <<endl;
  cout << "parallels lines with dircetion " << endl;
  cout << vectors[result.vertex2].a << " " << vectors[result.vertex2].b <<endl;
  cout << endl;
  auto p = make_pair(result, vectors[result.vertex2]);
  return p;

}


Triple Polygon::Get_max_gap() const{
  vector<Triple> diagonals (size_polygon * size_polygon);
  for(size_t i =0 ; i != size_polygon; i++){
    for(size_t j = 0; j != size_polygon; j++){
      diagonals[i* size_polygon + j].length = Get_length(points[i], points[j]);
      diagonals[i* size_polygon + j].vertex1 = i;
      diagonals[i * size_polygon + j].vertex2 = j;
    }
  }

  auto result = findMaxTriple(diagonals);
        
  Vector res_v(points[result.vertex1].x - points[result.vertex2].x, points[result.vertex1].y - points[result.vertex2].y );
  Vector perp(res_v);
  cout << result.length << endl;
  cout << "diagonal passes through the vertices : " << points[result.vertex1].x;
  cout << " " << points[result.vertex1].y << endl;
  cout << "diagonal passes through the vertices : " << points[result.vertex2].x;
  cout << " " << points[result.vertex2].y << endl;
  cout << "parallels lines with direction" << endl;
  cout << perp.a << " " << perp.b << endl;
  cout<< endl;
  return result;
        
}



Point calculateParallelPoint(const Point& basePoint, double direction_x, double direction_y, double offset) {
    return { basePoint.x + offset * direction_x, basePoint.y + offset * direction_y };
}


void drawPolygonWithParallelLines(const std::vector<Point>& points, int index1, int index2, double direction_x, double direction_y) {
    
    Gnuplot gp;

    std::vector<std::pair<double, double>> polygon;
    for (const auto& point : points) {
        polygon.emplace_back(point.x, point.y);
    }
    
    polygon.emplace_back(points[0].x, points[0].y);

    std::vector<std::pair<double, double>> line1, line2;

    for (double t = -10; t <= 10; t += 0.1) {
        
        Point p1 = calculateParallelPoint(points[index1], direction_x, direction_y, t);
        line1.emplace_back(p1.x, p1.y);

        Point p2 = calculateParallelPoint(points[index2], direction_x, direction_y, t);
        line2.emplace_back(p2.x, p2.y);
    }

    gp << "set title 'Polygon with Parallel Lines'\n";
    gp << "set grid\n";
    gp << "plot '-' with lines title 'Polygon', "
          "'-' with lines title 'Line 1', "
          "'-' with lines title 'Line 2'\n";

    gp.send1d(polygon);
    gp.send1d(line1);
    gp.send1d(line2);
}
