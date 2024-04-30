#include <stdio.h>
#include <math.h>
#define LIMIT 1000000

int sign(double x, double epsilon);
int root_half(double *x, double a, double b, double (*Function)(double), double epsilon);
