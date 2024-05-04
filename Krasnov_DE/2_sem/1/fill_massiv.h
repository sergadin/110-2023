#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double (*RRFun)(double);

double sine(double x);
double cubing(double x);
double reverseNum(double x);
double naturalLog(double x);


typedef enum {
	OK,
	MALLOC_ERR,
	INCORRECT_ARGUMENT
} error;

double fillValueArray(RRFun* functions, int func_num, double x, error* err,double *value_array);

