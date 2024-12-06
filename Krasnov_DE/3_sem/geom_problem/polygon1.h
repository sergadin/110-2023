#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
#include <utility>
#include "gnuplot-iostream.h"



using namespace std;

class Polygon;
class Line;
struct Point;
Point Find_intersection(Line &, Line &);

struct Point{
  double x;
  double y;
};

struct Triple{
    double length;
    int vertex1;
    int vertex2;
};

//The function Get_length calculates the distance between two points.
//Returns the length value
double Get_length(const Point &p1,const Point &p2);


//the function findMaxTriple takes as input an array consisting of a Triple structure
//and searches for the maximum element of the array by the first element (by the length of the segment)
Triple& findMaxTriple(vector<Triple>& diagonals);


//the function findMinTriple takes as input an array consisting of a Triple structure
//and searches for the minimum element of the array by the first element (by the length of the segment)
Triple& findMinTriple(vector<Triple>& diagonals);



class Vector {

friend class Polygon; // friend class declaration

protected:
    double a; // vector directions
    double b;

public:
    //constructor
    Vector(double a_v, double b_v);
    //destructor
    ~Vector();

    //functions return vector direction values(needs in main)
    double Get_a();

    double Get_b();

    //copy constructor, different from the standard one,
    //creates a new object of the Vector class, which is perpendicular to the copy vector
    Vector (const Vector& v1);

};


class Line : public Vector{ // inheritance is used

friend Point Find_intersection(Line&, Line&); //friend function declaration

private:
    Point origin;

public:
    //constructor
    Line(double x, double y, double a_l, double b_l);

    //destructor
    ~Line();

    //copy constructor
    Line(const Line& other);

    //direct output function (not used)
    void Print_Line() const;

};

//the function searches for the intersection point of two lines specified parametrically,
//returns the intersection point structure
//As input, the function receives constant references to two direct links
Point Find_intersection(Line &line_1,Line &line_2);



class Polygon{
private:
    unsigned int size_polygon;
    vector<Point> points;
    vector<Vector> vectors;

public:
    // constructor
    Polygon(unsigned size_p,const vector<Point>& points_p);

    //destructor
    ~Polygon();

    // copy constructor
    Polygon(const Polygon& p){}

    void Print_Polygon() const;

    double Get_vectors_product(int i, int j) const;

    //the function checks whether the polygon is convex, if not, the program throws exceptions
    bool Bulge_check() const;

    //void Get_min_gap() const;
    pair<Triple, Vector> Get_min_gap() const;

    Triple Get_max_gap() const;


};

Point calculateParallelPoint(const Point& basePoint, double direction_x, double direction_y, double offset);

void drawPolygonWithParallelLines(const std::vector<Point>& points, int index1, int index2, double direction_x, double direction_y);





