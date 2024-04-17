#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef double (*RRFun)(double);

typedef enum {
	OK,
	MALLOC_ERR,
	INCORRECT_ARGUMENT
} error;

double findMinValue(RRFun f, double a, double b, double eps, error* err);