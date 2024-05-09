#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double (*RRFun)(double);

typedef enum {
	OK,
    WRNG_ORD,
    LIMIT,
}error;

double Gauss_caunting(RRFun *f, double a, double b);
double Integral_count(RRFun *f, double a, double b, double eps, error *err);

