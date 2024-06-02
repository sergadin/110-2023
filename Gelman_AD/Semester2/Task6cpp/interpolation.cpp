#include <iostream>
#include <vector>
#include "interpolation.h"

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

    // Calculating approximate function values
    std::vector<double> result = linear_interpolation(x, y, x1);

    // Printing the results
    std::cout << "x1\ty1\tExact y1\n";
    for (size_t i = 0; i < x1.size(); i++) 
    {
        double exact_result = x1[i] * x1[i]; // Exact function values
        std::cout << x1[i] << "\t" << result[i] << "\t" << exact_result << std::endl;
    }
    return result;
}