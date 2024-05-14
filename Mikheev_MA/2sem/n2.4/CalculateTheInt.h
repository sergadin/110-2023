#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double (*RFun)(double);

typedef enum{
    LIMIT, 
    NOT_CORRECT,
    OK
}Er;


double CalculateTheInt(RFun f, double a, double b, double EPS, int *count, Er *error);