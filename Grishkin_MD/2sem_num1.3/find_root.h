#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef enum
{
    OK,
    ERR,
}Error;

Error error_code;

double find_root(double (*f)(double x), double a, double b, double eps);
