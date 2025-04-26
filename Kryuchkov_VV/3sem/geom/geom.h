#include <iostream>
#include <cmath>
#include <vector>
#include <bits/stdc++.h>
#include <stdlib.h>
#define eps 1e-10

using namespace std;

struct Point
{
    double x, y;
};


class ConvexPolygon
{
public:
    std::vector<Point> vertices_; // ������ ��� �������� ������ ��������������

    ConvexPolygon() = delete;

    ConvexPolygon(const std::vector<Point>& points); // �����������
    ConvexPolygon(const ConvexPolygon& other); // ����������� �����������
    ~ConvexPolygon(); // ����������

    void print() const
    {
        for (const auto& vertex : vertices_)
        {
            cout << "(" << vertex.x << ", " << vertex.y << ")" << endl;
        }
    };

    static int countPoints(const ConvexPolygon& points)
    {
        return points.vertices_.size(); // ���������� ���������� ��������� � �������.
    }

<<<<<<< HEAD
    static bool comparePoints(const Point& p1, const Point& p2) 
    {
        // ���������� �� ���������� x, ���� ��� �����, ���������� �� y
        if (abs(p1.x - p2.x) < 1e-10)
        {
=======
    static bool comparePoints(const Point& p1, const Point& p2) {
        // ���������� �� ���������� x, ���� ��� �����, ���������� �� y
        if (abs(p1.x - p2.x) < 0.0000000000000001) {
>>>>>>> 535ffd1 (check)
            return p1.y <= p2.y; // ���� x �����, ��������� �� y
        }
        return p1.x < p2.x; // ��������� �� x
    }

    // ������� ��� ���������� ������� �����
<<<<<<< HEAD
    static void sortPoints(ConvexPolygon& points) 
    {
=======
    static void sortPoints(ConvexPolygon& points) {
>>>>>>> 535ffd1 (check)
        std::sort(points.vertices_.begin(), points.vertices_.end(), comparePoints);
    }

    bool searchPoint(std::vector<Point> points, Point p);
    vector<Point> intersect(double a, double b, double c);
    double crossProduct(Point a, Point b, Point c);
    //vector<Point> intersection(Point a, Point b);
    vector<Point> pointsAboveAndBelowLine(Point a, Point b);
    static void writePolygon(const std::string& filename, const ConvexPolygon& points);
    static void writePolygonToFile(const std::string& filename, const ConvexPolygon& points);
    bool isSegmentInside(Point a, Point b);
    vector<vector<Point>> splitPolygon(const ConvexPolygon& poly1, const ConvexPolygon& poly2, const ConvexPolygon& poly3, const int t);

    ConvexPolygon& operator=(const ConvexPolygon& other);
};

class ConvexPolygon_Exception
{
private:
    int code_;
    std::string message_;
public:
    ConvexPolygon_Exception(int code, const std::string& message) : code_(code), message_(message) {}
    const std::string& message() const { return message_; }
    int code() const { return code_; }
};

ConvexPolygon::ConvexPolygon(const std::vector<Point>& points)
{
    vertices_ = points;
}

ConvexPolygon::ConvexPolygon(const ConvexPolygon& other)
{
    vertices_ = other.vertices_;
}

ConvexPolygon::~ConvexPolygon() {}



bool ConvexPolygon::searchPoint(std::vector<Point> points, Point p) 
{
    int n = points.size();
    for (int i = 0; i < n; i++) 
    {
        if ((abs(points[i].x - p.x) < 1e-10) && (abs(points[i].y - p.y) < 1e-10)) 
        {
            return true;
        }
    }
    return false;
}

// ������� ��� ���������� ���������� ������������ ���� ��������
<<<<<<< HEAD
double ConvexPolygon::crossProduct(Point a, Point b, Point c) 
{
=======
double ConvexPolygon::crossProduct(Point a, Point b, Point c) {
>>>>>>> 535ffd1 (check)
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}


vector<Point> ConvexPolygon::intersect(double a, double b, double c) 
{
    vector<Point> newPoints;
    int n = vertices_.size();

    for (int i = 0; i < n; i++) 
    {
        int next = (i + 1) % n;
        double val1 = a * vertices_[i].x + b * vertices_[i].y + c;
        double val2 = a * vertices_[next].x + b * vertices_[next].y + c;

        if (val1 * val2 <= 0) 
        {
            double x = (vertices_[i].x * abs(val2) + vertices_[next].x * abs(val1)) / (abs(val1) + abs(val2));
            double y = (vertices_[i].y * abs(val2) + vertices_[next].y * abs(val1)) / (abs(val1) + abs(val2));
            newPoints.push_back({ x,y });
        }

        if (abs(val2) < 1e-10) 
        {
            newPoints.push_back(vertices_[next]);
        }
    }

    cout << "Points of intersection:" << endl;
    for (auto p : newPoints) 
    {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }

    return newPoints;
}


// ������� ��� ������ ���� �������� �����, ������� ����� ������������ �������� ������ ������ � �����
<<<<<<< HEAD
vector<Point> ConvexPolygon::pointsAboveAndBelowLine(Point a, Point b) 
{
=======
vector<Point> ConvexPolygon::pointsAboveAndBelowLine(Point a, Point b) {
>>>>>>> 535ffd1 (check)
    vector<Point> above, below;
    int l = vertices_.size();
    for (int i = 0; i < l; i++) 
    {
        if (crossProduct(a, b, vertices_[i]) > 0) 
        {
            above.push_back(vertices_[i]);
        }
        else {
            below.push_back(vertices_[i]);
        }
    }
    cout << "Points above the line:" << endl;
    for (auto p : above) 
    {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }
    
    return above;
}

void ConvexPolygon::writePolygon(const std::string& filename, const ConvexPolygon& points)
{
    std::ofstream file(filename);

    for (const auto& point : points.vertices_)
    {
        file << point.x << " " << point.y << std::endl;
    }

    // �������� �������������, �������� ������ ����� � �����
    file << points.vertices_[0].x << " " << points.vertices_[0].y << std::endl;

    file.close();
}

void ConvexPolygon::writePolygonToFile(const std::string& filename, const ConvexPolygon& points)
{
    std::ofstream file(filename);

    for (const auto& point : points.vertices_)
    {
        file << point.x << " " << point.y << std::endl;
    }

    file.close();
}

// ������� ��� �������� ����� �� �������� ������� ������ ��������������
bool ConvexPolygon::isSegmentInside(Point a, Point b) 
{
<<<<<<< HEAD
    int n = vertices_.size()
    for (size_t i = 0; i < n; i++) 
    {
        int j = (i + 1) % n;
        if (crossProduct(vertices_[i], vertices_[j], a) * crossProduct(vertices_[i], vertices_[j], b) < 0) 
        {
=======
    size_t n = vertices_.size();
    for (size_t i = 0; i < n; i++) {
        int j = (i + 1) % n;
        if (crossProduct(vertices_[i], vertices_[j], a) * crossProduct(vertices_[i], vertices_[j], b) < 0) {
>>>>>>> 535ffd1 (check)
            return false; // ������� ���������� ������� ��������������
        }
    }
    return true; // ������� ������� ����� ������ ��������������
}


// ������� ��� ���������� �������������� ������
vector<vector<Point>> ConvexPolygon::splitPolygon(const ConvexPolygon& poly1, const ConvexPolygon& poly2, const ConvexPolygon& poly3, const int t)
{
    vector<vector<Point>> result;
    vector<Point> inters = poly1.vertices_;
    vector<Point> above = poly2.vertices_;
    vector<Point> polygon = poly3.vertices_;
    int k = 0;
    // ������� ����� ������������� (t = 5)

    vector<Point> a;
<<<<<<< HEAD
    for (int i = 0; i < polygon.size(); i++) 
    {  
=======
    for (size_t i = 0; i < polygon.size(); i++) {  
>>>>>>> 535ffd1 (check)
        if (searchPoint(above, polygon[i]) != searchPoint(above, polygon[i + 1]))
        {
            if (!(searchPoint(above, polygon[i])) && t != 5)
            {
                a.push_back(polygon[i]);
            }
            if (searchPoint(above, polygon[i]) && t == 5)
            {

                a.push_back(polygon[i]);
                a.push_back(inters[k]);
                result.push_back(a);
                a.push_back(inters[k-1]);

                /*
                cout << "Points of a:" << endl;
                for (auto p : a) {
                    cout << "(" << p.x << ", " << p.y << ")" << endl;
                }
                */

                writePolygonToFile("above.txt", a);
                vector<Point> a = {{ 0,0 }};
                //a.pop_back();
                k++;
                continue;
                //a.push_back(polygon[i]);
            }
            else
            {
                a.push_back(inters[k]);
                k++;
            }
        }
        /*else if (isSegmentInside(inters[k], inters[k + 1]) && searchPoint(above, polygon[i]) && (searchPoint(above, polygon[i]) != searchPoint(above, polygon[i + 1])) && t == 5)
        {
            a.push_back(polygon[i]);
            a.push_back(inters[k + 1]);
            result.push_back(a);
            a.clear();
            cout << "LOL" << endl;
        }*/
        else if ((t != 5) && !(searchPoint(above, polygon[i])))
        {
            a.push_back(polygon[i]);
        }
        else if ((t == 5) && searchPoint(above, polygon[i]))
        {
            a.push_back(polygon[i]);
        }

        if (t != 5)
        {
            writePolygon("below.txt", a);
        }
    }
    cout << "Points of a2:" << endl;
    for (auto p : a) 
    {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }
    result.push_back(a);
    a.clear();

    cout << "Size of result:" << result.size() << endl;

    return result;
}


// �������� ������������
ConvexPolygon& ConvexPolygon::operator=(const ConvexPolygon& other)
{
    // �������� ������ �� ������� �������
    vertices_ = other.vertices_;

    return *this; // ���������� ������ �� ������� ������
}