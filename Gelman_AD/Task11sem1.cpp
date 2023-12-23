#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Structure for storing a point
typedef struct Point 
{
    double x;
    double y;
} Point;

// Function for calculating the distance between two points
double distance(Point p1, Point p2) 
{
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}
 
double polygonDistance(Point* polygon_A, int lngth_A, Point* polygon_B, int lngth_B);

// Function for calculating the distance between two polygons
double polygonDistance(Point* polygon_A, int lngth_A, Point* polygon_B, int lngth_B)
{
    double minDistance = -1; // Minimum distance (= -1, in order to calculate the 0 distance if polygons touch)
    int i, j;

    // Calculating the distance between each point of the polygon A and each point of the polygon B
    for (i = 0; i < lngth_A; i++) 
    {
        for (j = 0; j < lngth_B; j++) 
        {
            double currDistance = distance(polygon_A[i], polygon_B[j]);
            if (minDistance == -1 || currDistance < minDistance) 
            {
                minDistance = currDistance;
            }
        }
    }

    return minDistance;
}

int main(void) 
{
    FILE* fileA;
    FILE* fileB;
    Point* polygon_A;
    Point* polygon_B;
    int lngth_A, lngth_B;

    fileA = fopen("in_A.txt", "r");
    fileB = fopen("in_B.txt", "r");

    if (fileA == NULL) 
    {
        printf("Error opening the fileA\n");
        return -1;
    }

    if (fileB == NULL) 
    {
        printf("Error opening the fileB\n");
        return -1;
    }

    // Reading files that stores a set of points defining each polygon
    fscanf(fileA, "%d", &lngth_A);
    fscanf(fileB, "%d", &lngth_B);

    if (fscanf(fileA, "%d", &lngth_A) != 1)
    {
        printf("Unable to read the file in_A\n");
        return -1;
        exit(-1);
    }

    if (fscanf(fileB, "%d", &lngth_B) != 1)
    {
        printf("Unable to read the file in_B\n");
        return -1;
        exit(-1);
    }

    // Creating arrays of points for each polygon
    polygon_A = (Point*)malloc((lngth_A) * sizeof(Point));
    polygon_B = (Point*)malloc((lngth_B) * sizeof(Point));

    if (polygon_A == NULL)
    {
        printf("Memory error\n");
        return -1;
    }

    if (polygon_B == NULL)
    {
        printf("Memory error\n");
        return -1;
    }

    // Reading the coordinates of the points of the polygon A from the file in_A
    for (int i = 0; i < lngth_A; i++)
    {
        fscanf(fileA, "%lf %lf", &polygon_A[i].x, &polygon_A[i].y);
    }

    for (int i = 0; i < lngth_B; i++)
    {
        fscanf(fileB, "%lf %lf", &polygon_B[i].x, &polygon_B[i].y);
    }

    // Calculating the distance between two polygons
    double distance = polygonDistance(polygon_A, lngth_A, polygon_B, lngth_B);
    printf("Distance: %lf\n", distance);

    free(polygon_A);
    free(polygon_B);

    fclose(fileA);
    fclose(fileB);

    return 0;
}