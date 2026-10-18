#include <cstdio>
#include <iostream>
#include <vector>

struct Point{
    double x;
    double y;
    int EqualsPoint(const Point& A);
};
//Структура точек

class Segment{
private:
    Point p{0, 0};
    Point q{0, 0};
public:
    Segment();
    Segment(const Point &pv, const Point &qv);
    Point P();
    Point Q();
    ~Segment();
};
//Класс отрезков
class Straight{
private:
    double a = 0;
    double b = 0;
    double c = 0;
public:
    Straight();
    Straight(double a, double b, double c);
    Straight(const Point& P, const Point &Q);
    double A();
    double B();
    double C();
    int Sign(const Point &P);
    ~Straight();
};
//Класс прямых

void draw(int N, std::vector<Segment> Segments, int color);
int InsectSegments(Segment I1, Segment I2);
int ExactlyPolygon(const std::vector<Segment> &Segments, int n);