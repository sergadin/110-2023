#include <iostream>
#include <cmath>
#include <vector>
#include <bits/stdc++.h>
#include <stdlib.h>
#include "geom.h"
#define eps 1e-10

int main() 
{
    //ConvexPolygon polygon({ {2, 0}, {2, 3}, {4, 2}, {7, 4}, {7, 0} }); // ��������� ����� ��������������

    double a = 0.6;
    double b = -1;
    double c = 0.8;

    Point lineStart = { 0, (-c / b) };
    Point lineEnd = { 1, (-a - c) / b };

    ConvexPolygon polygon0({ {0,0} });
    ConvexPolygon polygon({ {2, 0}, {2, 4}, {5, 2}, {9, 3}, {11, 6}, {12, 9}, {13, 10}, {14, 9}, {13, 5}, {13, 0} });
    ConvexPolygon polygon1(polygon.intersect(a, b, c));
    ConvexPolygon polygon2(polygon.pointsAboveAndBelowLine(lineStart, lineEnd));

/*
    cout << "Intersection points with the line:" << endl;
    polygon.intersect(-1, 5, -8); // Пример сечения прямой


    cout << endl;

    cout << "Points above and below the line:" << endl;
    polygon.pointsAboveAndBelowLine(lineStart, lineEnd);
    */

    //ConvexPolygon polygon1({ {2, 2}, {3.428, 2.285}, {4.857, 2.571}, {7, 3} });
    //ConvexPolygon polygon2({ {2, 3}, {7, 4} });

    //ConvexPolygon polygon2({ {2, 4}, {12, 9}, { 13, 10 } });
    //ConvexPolygon polygon3({ {2, 0}, {5, 2}, {9, 3}, {11, 6}, {14, 9}, {13, 5}, {13, 0} });
    //ConvexPolygon polygon1({ {2, 2}, {3.6, 2.9}, {11.6, 7.8}, {13.8, 9.2} });

    polygon.splitPolygon(polygon1, polygon2, polygon, 1);
    polygon0.splitPolygon(polygon1, polygon2, polygon, 5);

    cout << endl;

    cout << "Is segment inside the polygon? " << (polygon.isSegmentInside({ 1, 1 }, { 3, 6 }) ? "Yes" : "No") << endl;

    return 0;
}
