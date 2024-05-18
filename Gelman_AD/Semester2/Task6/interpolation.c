#include <stdio.h>
#include <stdlib.h>
#include "interpolation.h"

// Calculating the value of the function of the given point
double linear_interpolation(double x0, double y0, int n, double x1, double y1, double x);
double linear_interpolation(double x0, double y0, int n, double x1, double y1, double x)
{
    double result = 0;

    if (x >= x0 && x <= x1) 
    {
        result = y0 + (y1 - y0) / (x1 - x0) * (x - x0);
    }
    return result;
}

void interpolate(point* p, size_t n, point* i_p, size_t m, double* interp_y, error* err)
{
    *err = OK;
    double x1[m]; // Points from the net for interpolation
    double y11[m]; // The value of the function of the these points
    
    for (int j = 0; j < m; j++)
    {
        double x2, y2;
        int i;   
        
        // Searching for segment containing x
        for (i = 1; i < n; ++i)
        {
            if (p[i].x >= i_p[j].x)
                break;
        }

        double x0 = p[i - 1].x, x1 = p[i].x;
        double y0 = p[i - 1].y, y1 = p[i].y;
        double x = i_p[j].x;

        // Counting the approximate value of the function using the piecewise linear interpolation
        for (int i = 0; i < m; i++)
        {
            y11[i] = linear_interpolation(x0, y0, n, x1, y1, x); // Using the piecewise linear interpolation
        }

        // Weighting coefficients
        double L0 = ((x - x1) * (x - x2)) / ((x0 - x1) * (x0 - x2));
        double L1 = ((x - x0) * (x - x2)) / ((x1 - x0) * (x1 - x2));
        double L2 = ((x - x0) * (x - x1)) / ((x2 - x0) * (x2 - x1));

        double result = y0 * L0 + y1 * L1 + y2 * L2;

        interp_y[j] = result;
    }
}