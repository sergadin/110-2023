#include <iostream>
#include <vector>
#include "polygon_distance.h"

class MyClass
{
public:
    std::vector<double> x;       // The arguments of the function
    std::vector<double> y;      // The values of the function
    std::vector<double> x1;    // The given mesh for approximate function
};

// Function for calculating the values ​​of an approximate function on a given mesh using piecewise linear interpolation
std::vector<double> linear_interpolation(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& x1)
{
    std::vector<double> result;
    size_t n = x.size();

    for (size_t i = 0; i < x1.size(); i++)
    {
        size_t j = 0;
        while (x[j] < x1[i] && j < n - 1)
        {
            j++;
        }

        // Interpolation
        result.push_back(y[j] + (y[j + 1] - y[j]) / (x[j + 1] - x[j]) * (x1[i] - x[j]));
    }
    return result;
}

std::vector<double> interpolate(std::vector<double> x, std::vector<double> y, std::vector<double> x1, error* err)
{
    *err = OK;

    MyClass myObj;  // Create an object of MyClass

    // Calculating approximate function values
    std::vector<double> result = linear_interpolation(myObj.x, myObj.y, myObj.x1);

    // Printing the results
    std::cout << "myObj.x1\tmyObj.y1\texact_result\n";
    for (size_t i = 0; i < myObj.x1.size(); i++)
    {
        double exact_result = myObj.x1[i] * myObj.x1[i]; // Exact function values
        std::cout << myObj.x1[i] << "\t" << result[i] << "\t" << exact_result << std::endl;
    }
    return result;
}



// Look task 11 from yourself: I've had exactly the same task back in the 1st semester!

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct Point 
{
    double x, y;
};

// Функция для вычисления расстояния между двумя точками
double distance(Point p1, Point p2) 
{
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

// Функция для вычисления расстояния от точки до отрезка
double distanceToSegment(Point p, Point p1, Point p2) 
{
    double l2 = pow(distance(p1, p2), 2);
    if (l2 == 0) 
    {
        return distance(p, p1);
    }
    double t = std::max(0.0, std::min(1.0, ((p.x - p1.x) * (p2.x - p1.x) + (p.y - p1.y) * (p2.y - p1.y)) / l2));
    Point projection = { p1.x + t * (p2.x - p1.x), p1.y + t * (p2.y - p1.y) };
    return distance(p, projection);
}

// Функция для вычисления расстояния между двумя многоугольниками
double distanceBetweenPolygons(std::vector<Point> polygon1, std::vector<Point> polygon2) 
{
    double minDistance = std::numeric_limits<double>::max();

    for (size_t i = 0; i < polygon1.size(); i++) 
    {
        for (size_t j = 0; j < polygon2.size(); j++) 
        {
            minDistance = std::min(minDistance, distanceToSegment(polygon1[i], polygon2[j], polygon2[(j + 1) % polygon2.size()]));
        }
    }

    for (size_t i = 0; i < polygon2.size(); i++) 
    {
        for (size_t j = 0; j < polygon1.size(); j++) 
        {
            minDistance = std::min(minDistance, distanceToSegment(polygon2[i], polygon1[j], polygon1[(j + 1) % polygon1.size()]));
        }
    }

    return minDistance;
}

int main() 
{
    std::vector<Point> polygon1 = { {1, 1}, {2, 2}, {3, 2}, {2, 1} };
    std::vector<Point> polygon2 = { {5, 5}, {6, 6}, {7, 5} };

    double distance = distanceBetweenPolygons(polygon1, polygon2);
    std::cout << "Distance between polygons: " << distance << std::endl;

    return 0;
}