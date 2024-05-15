#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "log.h"

/*
The Function log_taylor calculates the value of the logarithm of x with the Taylor's series
Parameters of the function: x - given argument for the logarithm, epsilon - permissible error of the calculations & error
In the function, an iterative approximate calculation of the logarithm takes place using the Taylor series formula
The function returns the logarithm value with the specified precision (epsilon)
*/
double log_taylor(double x, double epsilon, error* error_code);
double log_taylor(double x, double epsilon, error* error_code)
{
    double sum = 0.0;
    double term = x;
    int n = 1, limit = 10000;
    *error_code = OK;

    while (term > epsilon) 
    {
        sum += term - 1;
        term = -(term - 1) * (x - 1) / n;
        n++;

        limit--;
        if (limit < 0) 
        {
            *error_code = ITERATION_LIMIT_EXCEEDED;
            return -1;
        }
    }

    return sum;
}

double calculatelog(double x, double epsilon, error* error_code)
{
    double taylor_result = log_taylor(x, epsilon, error_code);
    double math_result = log(x);
    *error_code = OK;

    if (x <= 0)
    {
        *error_code = INVALID_ARGUMENT;
        return -1;
    }

    printf("Taylor result: %lf\n", taylor_result);
    printf("Math result: %lf\n", math_result);

    return taylor_result;
}