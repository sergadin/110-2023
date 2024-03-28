#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double (*RRFun)(double);

typedef enum {
	OK,
	MALLOC_ERR,
	INCORRECT_ARGUMENT
} error;

double* fillValueArray(RRFun* functions, int func_num, double x, error* err);