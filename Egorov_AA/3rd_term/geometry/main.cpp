#include <iostream>
#include <vector>
#include <iomanip>

class Point {
public:
    static int index_global;
    double x, y;
    int index;
    bool belongs_to_poly;
    Point() : index(Point::index_global++) {}
    Point(double x, double y) : x(x), y(y), index(Point::index_global++), belongs_to_poly(true) {}
    Point(double x, double y, int index, bool flag) : x(x), y(y), index(index), belongs_to_poly(flag) {}

    bool operator==(const Point& other) const {
        if ((std::fabs(x - other.x) > 1e-9) || (std::fabs(y - other.y) > 1e-9)) {
            return false;
        }
        return true;
    }

};
int Point::index_global = 1;

class Line {
public:
    Point p1, p2;
    Line() {}
    Line(Point a, Point b) : p1(a), p2(b) {}

    double findCoeffA() {
        return p1.y - p2.y;
    }

    double findCoeffB() {
        return p2.x - p1.x;
    }

    double findCoeffC() {
        return -((p1.y - p2.y) * p1.x + (p2.x - p1.x) * p1.y);
    }
};

class Cross {
public:
    bool is_dot = false;
    int index_of_dot;
    Point point;
    Cross() {}
    Cross(bool flag, int index, Point p) : is_dot(flag), index_of_dot(index), point(p) {}
};

class Polygon : public std::vector<Point> {
public:
    Polygon() {}
    Polygon(std::vector<Point> p) : std::vector<Point>(p) {}
};

std::vector<Cross> findIntersected(Polygon poly, Line l) {

    std::vector<Cross> intersected_points = {};

    int index_of_intersected_point = 0;

    double a = l.findCoeffA();
    double b = l.findCoeffB();
    double c = l.findCoeffC();

    for (int i = 0; i < (poly.size() - 1); i++) {
        double x1 = poly[i].x, y1 = poly[i].y,
            x2 = poly[i + 1].x, y2 = poly[i + 1].y,
            xi, yi;
        double denominator = a * (x2 - x1) + b * (y2 - y1);
        if (std::abs(denominator) < 1e-9) {
            if (std::abs(a * x1 + b * y1 + c < 1e-9 && std::abs(a * x2 + b * y2 + c) < 1e-9)) {
                continue;
            }
            continue;
        }

        double t = -(a * x1 + b * y1 + c) / denominator;
        if (t < 0 || t > 1)
            continue;

        xi = x1 + t * (x2 - x1);
        yi = y1 + t * (y2 - y1);

        if (index_of_intersected_point > 0) {
            if ((std::abs(xi - intersected_points[index_of_intersected_point - 1].point.x) < 1e-9) &&
                (std::abs(yi - intersected_points[index_of_intersected_point - 1].point.y) < 1e-9)) {
                intersected_points[index_of_intersected_point - 1].index_of_dot = i + 1;
                intersected_points[index_of_intersected_point - 1].is_dot = true;
                continue;
            }
        }

        if (std::min(x1, x2) - 1e-9 <= xi && xi <= std::max(x1, x2) + 1e-9 &&
            std::min(y1, y2) - 1e-9 <= yi && yi <= std::max(y1, y2) + 1e-9) {
            intersected_points.insert(intersected_points.begin() + index_of_intersected_point, Cross(false, i + 1, Point(xi, yi)));
            index_of_intersected_point++;
        }

    }

    std::cout << "\n\n";

    for (Cross& c : intersected_points) {
        std::cout << c.point.x << "\t" << c.point.y << "\t" << c.index_of_dot << "\t" << c.is_dot << "\n";
    }

    return intersected_points;
}


bool isPointOnSegment(Point p, Point p1, Point p2) {
    double crossProduct = (p.y - p1.y) * (p2.x - p1.x) - (p.x - p1.x) * (p2.y - p1.y);
    if (std::abs(crossProduct) > 1e-9) {
        return false;
    }

    if (p.x < std::min(p1.x, p2.x) || p.x > std::max(p1.x, p2.x)) {
        return false;
    }
    if (p.y < std::min(p1.y, p2.y) || p.y > std::max(p1.y, p2.y)) {
        return false;
    }

    return true;
}


bool isIntersecting(Point p, Point p1, Point p2) {
    if (p1.y > p2.y) {
        std::swap(p1, p2);
    }
    if (p.y == p1.y || p.y == p2.y) {
        p.y += 1e-9;
    }

    if (p.y < p1.y || p.y > p2.y) {
        return false;
    }
    if (p.x >= std::max(p1.x, p2.x)) {
        return false;
    }

    double xIntersection = p1.x + (p.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
    return p.x < xIntersection;
}


bool isPointInsidePolygon(const Polygon& polygon, Point p) {
    int intersections = 0;
    for (size_t i = 0; i < polygon.size(); ++i) {
        Point p1 = polygon[i];
        Point p2 = polygon[(i + 1) % polygon.size()];

        if (isPointOnSegment(p, p1, p2)) {
            return false;

        }
        if (isIntersecting(p, p1, p2)) {
            ++intersections;
        }
    }
    return intersections % 2 == 1;
}


int main() {
    std::cout << std::fixed << std::setprecision(2) << "x\ty\tindex\n";
    Polygon poly = std::vector<Point>({ Point(5, 2), Point(2, 5), Point(5, 6), Point(4, 8), Point(6, 10), Point(7, 14), Point(10, 6), Point(9, 4), Point(6, 4), Point(5, 2) });
    for (Point p : poly) {
        std::cout << p.x << "\t" << p.y << "\t" << p.index << "\n";
    }
    std::vector<Cross> cs = findIntersected(poly, Line(Point(0, 4), Point(6, 10)));
    Point::index_global = 1;

    Polygon new_poly = poly;
    int num_of_ins = 0;

    for (Cross c : cs) {
        if (c.is_dot) {
            new_poly[c.index_of_dot].belongs_to_poly = false;
            new_poly[c.index_of_dot].index = poly.size() + num_of_ins + 1;
        }
        else {
            new_poly.insert(new_poly.begin() + c.index_of_dot + num_of_ins, Point(c.point.x, c.point.y, poly.size() + num_of_ins + 1, false));
            ++num_of_ins;
        }
    }

    std::cout << "\n\nx\ty\tindex\n";
    for (Point& p : new_poly) {
        std::cout << p.x << "\t" << p.y << "\t" << p.index << "\t" << p.belongs_to_poly << "\n";
    }
    std::cout << "\n";

    std::vector<Polygon> new_polys_array;

    Polygon temp_poly;
    int intersect_point_flag = 1;
    int i = 0, j = 0, index_of_temp_poly = 0;

    temp_poly.insert(temp_poly.begin(), new_poly[0]);
    i++;
    index_of_temp_poly++;

    while (true) {
        if (new_poly[i] == new_poly[0]) {
            int index_of_zero_poly = 0;
            for (Point p : temp_poly) {
                new_polys_array[0].insert(new_polys_array[0].begin() + index_of_zero_poly, p);
                index_of_zero_poly++;
            }
            break;
        }
        if (new_poly[i].belongs_to_poly) {
            temp_poly.insert(temp_poly.begin() + index_of_temp_poly, new_poly[i]);
            i++;
            index_of_temp_poly++;
        }
        else if (intersect_point_flag % 2) {
            temp_poly.insert(temp_poly.begin() + index_of_temp_poly, new_poly[i]);
            new_polys_array.insert(new_polys_array.begin() + j, temp_poly);
            j++;
            temp_poly.erase(temp_poly.begin(), temp_poly.end());
            index_of_temp_poly = 0;
            intersect_point_flag++;
        }
        else {
            temp_poly.insert(temp_poly.begin() + index_of_temp_poly, new_poly[i]);
            intersect_point_flag++;
            i++;
            index_of_temp_poly++;
        }
    }


    for (int k = 0; k < new_polys_array.size(); k++) {
        double xc = (new_polys_array[k][0].x + new_polys_array[k][new_polys_array[k].size() - 1].x) / 2;
        double yc = (new_polys_array[k][0].y + new_polys_array[k][new_polys_array[k].size() - 1].y) / 2;

        if (!isPointInsidePolygon(poly, Point(xc, yc))) {
            new_polys_array.erase(new_polys_array.begin() + k);
            k--;
        }

    }
    std::cout << "\n\n";



    for (Polygon pol : new_polys_array) {
        for (Point poi : pol) {
            std::cout << "(" << poi.x << ", " << poi.y << ")" << " ";
        }
        std::cout << "\n";
    }
}