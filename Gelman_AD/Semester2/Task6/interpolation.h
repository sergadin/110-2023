#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    double x, y;
} point;

typedef enum
{
    OK,
} error;

void interpolate(point* p, size_t n, point* i_p, size_t m, double* interp_y, error* err);

/*
A function for calculating approximate values ​​from the given points
The function input is an array of given points (p), the number of these points (n),
An array with points at which it is needed to find the value (i_p), the number of these points (m),
An array where will be the required values ​​(interp_y) and a pointer to the error code (err).

The three closest points to the desired one are found and using the formulas of weighting coefficients 
And the formula of the piecewise linear interpolation we find the approximate value of a point.

If everything went well, the function values ​of the required points will be written to the interp_y array.
The given and received points will be written to new files. 
With the help of gnuplot, the following will appear in the folder: pictures of given functions and obtained points.
*/
