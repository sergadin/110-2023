#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "interpolation.h"

// Function for calculating the values ​​of an approximate function on a given mesh using piecewise linear interpolation
std::vector<double> linear_interpolation(const std::vector<double>& x0, const std::vector<double>& y0, int n,
    const std::vector<double>& x1, const std::vector<double>& y1, const std::vector<double>& x)
{
    std::vector<double> result;

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

void interpolate(point* p, size_t n, point* i_p, size_t m, double* interp_y, error* err)
{
    *err = OK;

    // Calculating approximate function values
    std::vector<double> result = linear_interpolation(x0, y0, n, x1, y1);

    // Printing the results
    std::cout << "x1\ty1\tExact y1\n";
    for (size_t i = 0; i < x1.size(); i++) 
    {
        double exact_result = x1[i] * x1[i]; // Exact function values
        std::cout << x1[i] << "\t" << result[i] << "\t" << exact_result << std::endl;
    }
}