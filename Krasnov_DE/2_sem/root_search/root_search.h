#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double (*RRFun)(double);


typedef enum {
	OK,     /*no mistakes*/
    WRNG_ORD, /*the left end of the segment is greater than the right*/
    EQUAL_VAL, /*there are identical values ​​inside the segment*/
	NO_ROOT /*there are no roots on the segment*/
}error;

double root_search(RRFun *f, double a, double b, double eps, error *err);




