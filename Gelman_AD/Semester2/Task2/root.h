#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double (*RRFun)(double);

typedef enum //Errors
{           
	OK,
	ITERATION_LIMIT_EXCEEDED,
	WRONG_INTERVAL,
	NOT_APPLICABLE
} error;

/* 
Function return value: 
zero, if the root was not found (the method is not applicable)
positive integer, corresponding to the number of method iterations, if the method is applicable.
*/

int root_chords(double* x, double a, double b, double (*function)(double), double epsilon);

/*
if sign(f(a)) = 0, sign(f(b)) = 0, sign(f(a)) = sign(f(b)) the iteration method will not start
if sign(f(a)) = 0 or sign(f(b)) = 0, the required root is returned (one if there are two of them)
*/