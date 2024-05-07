#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double (*RRFun)(double);

typedef enum {
	OK, // no mistakes
    WRNG_ORD, // the ends of the segment are entered incorrectly
    LIMIT, // the limit of performed operations has been exceeded
}error;

double min_search(RRFun *f, double a, double b, double eps, error *err);

