#include <iostream>
#include <cmath>

using namespace std;

// Класс точки
class Point {
public:
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}

    double distance(const Point& other) const {
        return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
    }
};

// Класс много угольника
class Polygon {
private:
    Point* vertices;  // Массив вершин (динамический)
    size_t vertexCount; // Количество вершин
    size_t capacity; // Емкость массива (для добавления вершин)

public:
    Polygon(size_t initialCapacity = 4) : vertexCount(0), capacity(initialCapacity) {
        vertices = new Point[capacity];
    }

    ~Polygon() {
        delete[] vertices;
    }

    void addVertex(const Point& p) {
        if (vertexCount == capacity) {
            // Увеличиваем размер массива, если он полон
            capacity *= 2;
            Point* newVertices = new Point[capacity];  // Новый массив с удвоенной емкостью
            for (size_t i = 0; i < vertexCount; ++i) {
                newVertices[i] = vertices[i];  // Копируем старые вершины в новый массив
            }
            delete[] vertices;  // Освобождаем старый массив
            vertices = newVertices;  // Перенаправляем указатель на новый массив
        }
        vertices[vertexCount++] = p;  // Добавляем новую вершину
    }

    // Получение количества вершин
    size_t getVertexCount() const {
        return vertexCount;
    }

    // Вычисление периметра
    double getPerimeter() const {
        double perimeter = 0.0;
        for (size_t i = 0; i < vertexCount; ++i) {
            perimeter += vertices[i].distance(vertices[(i + 1) % vertexCount]);  // Расстояние между соседними вершинами
        }
        return perimeter;
    }

    // Вычисление площади методом Гаусса ы
    double getArea() const {
        double area = 0.0;
        for (size_t i = 0; i < vertexCount; ++i) {
            const Point& p1 = vertices[i];
            const Point& p2 = vertices[(i + 1) % vertexCount];
            area += (p1.x * p2.y) - (p1.y * p2.x);
        }
        return fabs(area) / 2.0;
    }

    // Вывод информации о многоугольнике
    void print() const {
        cout << "Polygon vertices:\n";
        for (size_t i = 0; i < vertexCount; ++i) {
            cout << "(" << vertices[i].x << ", " << vertices[i].y << ")\n";
        }
    }
};