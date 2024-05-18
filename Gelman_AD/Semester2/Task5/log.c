#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "log.h"

/*
The Function calculatelog calculates the value of the logarithm of x with the Taylor's series
Parameters of the function: x - given argument for the logarithm, epsilon - permissible error of the calculations & error
In the function, an iterative approximate calculation of the logarithm takes place using the Taylor series formula
The function returns the logarithm value with the specified precision (epsilon)
*/

double power_n(double x, int n);
double power_n(double x, int n)
{
    double y = 1;
    for (int i = 0; i < n; i++)
    {
        y = y * x;
    }
    return y;
}

double calculatelog(double x, double epsilon, error* error_code)
{
    double taylor_result = 0;
    int n = 1, limit = 10000;
    double n_member = x;

    if (x <= 0)
    {
        *error_code = INVALID_ARGUMENT;
        return -1;
    }

    while (fabs(n_member) >= epsilon)
    {
        taylor_result += n_member;
        n++;
        if (n % 2 == 0) // for odd members
        {
            n_member = ((-1) * power_n(x, n)) / n;
        }
        else // for even members
        {
            n_member = power_n(x, n) / n;
        }
        limit--;
        if (limit < 0)
        {
            *error_code = ITERATION_LIMIT_EXCEEDED;
            return -1;
        }
    }
    *error_code = OK;
    printf("Taylor result: %lf\n", taylor_result);
    return taylor_result;
}