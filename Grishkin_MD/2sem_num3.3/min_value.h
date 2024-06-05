#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum
{
    OK,
    ERR,
}Error;

Error error_code;

double min_value(double (*f)(double x), double a, double b,  double eps);
