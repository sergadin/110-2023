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
    std::vector<Point> vertices_; // Вектор для хранения вершин многоугольника

    ConvexPolygon() = delete;

    ConvexPolygon(const std::vector<Point>& points); // Конструктор
    ConvexPolygon(const ConvexPolygon& other); // Конструктор копирования
    ~ConvexPolygon(); // Деструктор

    void print() const
    {
        for (const auto& vertex : vertices_)
        {
            cout << "(" << vertex.x << ", " << vertex.y << ")" << endl;
        }
    };

    static int countPoints(const ConvexPolygon& points)
    {
        return points.vertices_.size(); // Возвращает количество элементов в векторе.
    }

    void addPoint(int x, int y) {
        vertices_.push_back(Point(x, y));
    }

    void intersect(double a, double b, double c) {
        vector<Point> newPoints;
        int n = points.size();

        for (int i = 0; i < n; i++) {
            int next = (i + 1) % n;
            double val1 = a * points[i].x + b * points[i].y + c;
            double val2 = a * points[next].x + b * points[next].y + c;

            if (val1 * val2 <= 0) {
                double x = (points[i].x * abs(val2) + points[next].x * abs(val1)) / (abs(val1) + abs(val2));
                double y = (points[i].y * abs(val2) + points[next].y * abs(val1)) / (abs(val1) + abs(val2));
                newPoints.push_back(Point(x, y));
            }

            if (val2 == 0) {
                newPoints.push_back(points[next]);
            }
        }

        points = newPoints;
    }



    // Функция для проверки положения точки относительно прямой (лево/право)
    int orientation(Point p1, Point p2, Point p3) {
        int val = (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);
        if (val == 0) return 0; // коллинеарны
        return (val > 0) ? 1 : 2; // влево или вправо
    }

    // Функция для нахождения точек пересечения отрезка с прямой
    Point intersect(Point p1, Point p2, int a, int b, int c) {
        Point intersectPoint;
        intersectPoint.x = (b * (b * p1.x - a * p1.y) - a * c) / (a * a + b * b);
        intersectPoint.y = (a * (-b * p1.x + a * p1.y) - b * c) / (a * a + b * b);
        return intersectPoint;
    }

    // Функция для разделения многоугольника прямой
    vector<vector<Point>> splitPolygon(vector<Point> polygon, Point p1, Point p2) {
        vector<vector<Point>> result;
        int n = polygon.size();
        vector<int> side(n); // Массив для хранения положения точек относительно прямой

        // Определяем положение каждой точки многоугольника относительно прямой
        for (int i = 0; i < n; i++) {
            side[i] = orientation(p1, p2, polygon[i]);
        }

        // Создаем два новых многоугольника
        vector<Point> leftPolygon, rightPolygon;
        for (int i = 0; i < n; i++) {
            int next = (i + 1) % n;
            if (side[i] == 1) leftPolygon.push_back(polygon[i]);
            if (side[i] == 2) rightPolygon.push_back(polygon[i]);
            if (side[i] == 0) {
                leftPolygon.push_back(polygon[i]);
                rightPolygon.push_back(polygon[i]);
            }
            if (side[i] * side[next] == 3) {
                Point intersectPoint = intersect(polygon[i], polygon[next], p1.y - p2.y, p2.x - p1.x, p1.x * p2.y - p1.y * p2.x);
                leftPolygon.push_back(intersectPoint);
                rightPolygon.push_back(intersectPoint);
            }
        }

        result.push_back(leftPolygon);
        result.push_back(rightPolygon);

        return result;
    }



    static double cross(const Point& a, const Point& b);
    static bool isPointInPolygon(const Point& p, const ConvexPolygon& polygon);

    ConvexPolygon& operator=(const ConvexPolygon& other);
   // friend ConvexPolygon operator*(const ConvexPolygon& poly1, const ConvexPolygon& poly2);
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



// Определитель для векторного произведения
double ConvexPolygon::cross(const Point& a, const Point& b)
{
    return (a.x * b.y - a.y * b.x);
}

// Оператор присваивания
ConvexPolygon& ConvexPolygon::operator=(const ConvexPolygon& other)
{
    // Копируем данные из другого объекта
    vertices_ = other.vertices_;

    return *this; // Возвращаем ссылку на текущий объект
}

// ConvexPolygon operator*(const ConvexPolygon& poly1, const ConvexPolygon& poly2)



int main() {
    ConvexPolygon poly({2, 0});
    poly.addPoint(2, 0);
    poly.addPoint(2, 3);
    poly.addPoint(4, 2);
    poly.addPoint(7, 4);
    poly.addPoint(7, 0);

    poly.intersect(-1, 5, -8); // Пример сечения прямой x - y - 2 = 0

    vector<Point> polygon = { {2, 0}, {2, 3}, {4, 2}, {7, 4}, {7, 0} };
    Point p1 = { 2, 2 };
    Point p2 = { 7, 3 };

    ConvexPolygon poly2;
    ConvexPolygon poly3;

    vector<vector<Point>> splitPolygons = splitPolygon(polygon, p1, p2);

    for (auto point : splitPolygons[0]) {
        poly2.vertices_.addPoint(point.x, point.y);
    }

    for (auto point : splitPolygons[1]) {
        poly3.vertices_.addPoint(point.x, point.y);
    }

    return 0;

}