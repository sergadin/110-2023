#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} point;

void interpolate(point* points, int num_points, double* interp_points, int num_interp, double* interp_values);
