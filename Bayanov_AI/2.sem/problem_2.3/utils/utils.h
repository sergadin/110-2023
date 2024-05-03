#include <stdio.h>
#include <math.h>
#define LIMIT 1000

typedef enum {
	OK,
    ERROR_BORDERS,
    ERROR_LIMIT,
}ERROR;

static double Simpson(double a, double b, double (*Function)(double));
double integral(double a, double b, double (*Function)(double), double epsilon, ERROR *error);
