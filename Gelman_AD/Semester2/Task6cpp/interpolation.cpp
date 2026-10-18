#include <iostream>
#include <vector>
#include "interpolation.h"

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