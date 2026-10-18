#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct Point
{
    double x, y;
};

class ConvexPolygon
{
private:
    // Vector for the vertices of the polygon
    std::vector<Point> vertices_;
public:
    ConvexPolygon() = delete;
    ConvexPolygon(const std::vector<Point>& points); // Constructor
    ConvexPolygon(const ConvexPolygon& other); // Copying constructor
    ~ConvexPolygon(); // Destructor

    void print() const
    {
        for (const auto& vertex : vertices_)
        {
            cout << "(" << vertex.x << ", " << vertex.y << ")" << endl;
        }
    };

    static int count_points(const ConvexPolygon& points)
    {
        return points.vertices_.size(); // The number of the vertices in a vector
    }

    static double distance(const Point& p1, const Point& p2);
    static double distance_to_segment(const Point& p, const Point& a, const Point& b);
    static bool is_polygons_intersect(const ConvexPolygon& polygon1, const ConvexPolygon& polygon2);

    friend double operator+(const ConvexPolygon& other1, const ConvexPolygon& other2);
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

// Function for couting the distance between two points
double ConvexPolygon::distance(const Point& p1, const Point& p2)
{
    return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

// Function for couting the distance between a point and a vector
double ConvexPolygon::distance_to_segment(const Point& p, const Point& a, const Point& b)
{
    double l2 = (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
    if (l2 == 0) return distance(p, a);

    double t = (((p.x - a.x) * (b.x - a.x) + (p.y - a.y) * (b.y - a.y)) / l2);
    t = std::max(0.0, std::min(1.0, t));
    Point projection;
    projection.x = (a.x + t * (b.x - a.x));
    projection.y = (a.y + t * (b.y - a.y));

    return distance(p, projection);
}

// Function for checking the intersection of the polygons
bool ConvexPolygon::is_polygons_intersect(const ConvexPolygon& polygon1, const ConvexPolygon& polygon2)
{
    for (int i = 0; i < polygon1.vertices_.size(); ++i)
    {
        for (int j = 0; j < polygon2.vertices_.size(); ++j)
        {
            if (distance_to_segment(polygon1.vertices_[i], polygon2.vertices_[j], polygon2.vertices_[(j + 1) % polygon2.vertices_.size()]) == 0)
            {
                return true;
            }
        }
    }

    return false;
}

// Function for counting the distance between two polygons
double operator+(const ConvexPolygon& poly1, const ConvexPolygon& poly2)
{
    double min_distance = INFINITY;

    if (ConvexPolygon::is_polygons_intersect(poly1, poly2))
    {
        min_distance = 0;
        return min_distance;
    }

    for (int i = 0; i < poly1.vertices_.size(); ++i)
    {
        for (int j = 0; j < poly2.vertices_.size(); ++j)
        {
            min_distance = std::min(min_distance, ConvexPolygon::distance_to_segment(poly1.vertices_[i], poly2.vertices_[j], poly2.vertices_[(j + 1) % poly2.vertices_.size()]));
            min_distance = std::min(min_distance, ConvexPolygon::distance_to_segment(poly2.vertices_[j], poly1.vertices_[i], poly1.vertices_[(i + 1) % poly1.vertices_.size()]));
        }
    }

    return min_distance;
}