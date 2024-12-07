#include <iostream>
#include <cmath>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

struct Point
{
    double x, y;
};


class ConvexPolygon
{
public:
    std::vector<Point> vertices_;

    ConvexPolygon() = delete;

    ConvexPolygon(const std::vector<Point>& points);
    ConvexPolygon(const ConvexPolygon& other);
    ~ConvexPolygon();

    void print() const
    {
        for (const auto& vertex : vertices_)
        {
            cout << "(" << vertex.x << ", " << vertex.y << ")" << endl;
        }
    };

    static int countPoints(const ConvexPolygon& points)
    {
        return points.vertices_.size();
    }

    static bool comparePoints(const Point& p1, const Point& p2) 
    {
        if (p1.x == p2.x) 
        {
            return p1.y <= p2.y;
        }
        return p1.x < p2.x;
    }

    static void sortPoints(ConvexPolygon& points) {
        std::sort(points.vertices_.begin(), points.vertices_.end(), comparePoints);
    }

    bool searchPoint(std::vector<Point> points, Point p);
    void intersect(double a, double b, double c);
    double crossProduct(Point a, Point b, Point c);
    void intersection(Point a, Point b);
    void pointsAboveAndBelowLine(Point a, Point b);
    bool isSegmentInside(Point a, Point b);
    vector<vector<Point>> splitPolygon(const ConvexPolygon& poly1, const ConvexPolygon& poly2, const ConvexPolygon& poly3);

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



bool ConvexPolygon::searchPoint(std::vector<Point> points, Point p) {
    for (int i = 0; i < points.size(); i++) {
        if (points[i].x == p.x && points[i].y == p.y) {
            return true;
        }
    }
    return false;
}

double ConvexPolygon::crossProduct(Point a, Point b, Point c) 
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}


void ConvexPolygon::intersect(double a, double b, double c) 
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
            newPoints.push_back({x,y});
        }

        if (val2 == 0) {
            newPoints.push_back(vertices_[next]);
        }
    }

    cout << "Points of intersection:" << endl;
    for (auto p : newPoints) {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }
}

void ConvexPolygon::pointsAboveAndBelowLine(Point a, Point b) 
{
    vector<Point> above, below;
    for (int i = 0; i < vertices_.size(); i++) {
        if (crossProduct(a, b, vertices_[i]) > 0) {
            above.push_back(vertices_[i]);
        }
        else {
            below.push_back(vertices_[i]);
        }
    }
    cout << "Points above the line:" << endl;
    for (auto p : above) {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }
    cout << "Points below the line:" << endl;
    for (auto p : below) {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }
}


bool ConvexPolygon::isSegmentInside(Point a, Point b) {
    for (int i = 0; i < vertices_.size(); i++) {
        int j = (i + 1) % vertices_.size();
        if (crossProduct(vertices_[i], vertices_[j], a) * crossProduct(vertices_[i], vertices_[j], b) < 0) {
            return false;
        }
    }
    return true;
}

vector<vector<Point>> ConvexPolygon::splitPolygon(const ConvexPolygon& poly1, const ConvexPolygon& poly2, const ConvexPolygon& poly3)
{
    vector<vector<Point>> result;
    vector<Point> inters = poly1.vertices_;
    vector<Point> above = poly2.vertices_;
    vector<Point> polygon = poly3.vertices_;
    int k = 0;
    int t = 5;

        vector<Point> a;
        for (int i = 0; i < polygon.size(); i++) {

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
                     cout << "LOL" << endl;
                     cout << "Points of a:" << endl;
                     for (auto p : a) {
                         cout << "(" << p.x << ", " << p.y << ")" << endl;
                     }
                     a.clear();
                     k++;
                     continue;
                }
                else
                {
                    a.push_back(inters[k]);
                    k++;
                }
            }

            else if ((t != 5) && !(searchPoint(above, polygon[i])))
            {
                a.push_back(polygon[i]);
            }
            else if ((t == 5) && searchPoint(above, polygon[i]))
            {
                a.push_back(polygon[i]);
            }

         
        }
        cout << "Points of a2:" << endl;
        for (auto p : a) {
            cout << "(" << p.x << ", " << p.y << ")" << endl;
        }
        result.push_back(a);
        a.clear();

    cout << "Size of result:" << result.size() << endl;

    return result;
}


ConvexPolygon& ConvexPolygon::operator=(const ConvexPolygon& other)
{
    vertices_ = other.vertices_;

    return *this;
}









int main() {

    ConvexPolygon polygon({ {2, 0}, {2, 4}, {5, 2}, {9, 3}, {11, 6}, {12, 9}, {13, 10}, {14, 9}, {13, 5}, {13, 0} });

    Point lineStart = { 2, 2 };
    Point lineEnd = { 7, 5 };

    cout << "Intersection points with the line:" << endl;
    polygon.intersect(-1, 5, -8);

    cout << endl;

    cout << "Points above and below the line:" << endl;
    polygon.pointsAboveAndBelowLine(lineStart, lineEnd);

    ConvexPolygon polygon2({ {2, 4}, {12, 9}, { 13, 10 } });
    ConvexPolygon polygon3({ {2, 0}, {5, 2}, {9, 3}, {11, 6}, {14, 9}, {13, 5}, {13, 0} });
    ConvexPolygon polygon1({ {2, 2}, {3.6, 2.9}, {11.6, 7.8}, {13.8, 9.2} });

    polygon.splitPolygon(polygon1, polygon2, polygon);

    cout << endl;

    cout << "Is segment inside the polygon? " << (polygon.isSegmentInside({ 1, 1 }, { 3, 6 }) ? "Yes" : "No") << endl;

    return 0;
}
