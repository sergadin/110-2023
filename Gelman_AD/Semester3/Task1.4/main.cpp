#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "polygon_distance.h"


int main() 
{
    double distance;

    ConvexPolygon polygon1({ {0, 0}, {3, 0}, {4, 4}, {0, 3} });
    ConvexPolygon polygon2({ {4, 4}, {6, 4}, {6, 6}, {4, 7} });

    distance = polygon1 + polygon2;
    cout << "The distance between two polygons equals " << distance << std::endl;

    return 0;
}