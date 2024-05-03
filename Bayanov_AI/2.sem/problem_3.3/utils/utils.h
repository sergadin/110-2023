#include <stdio.h>
#include <math.h>
#define LIMIT 1000

typedef enum {
	OK,
    ERROR_BORDERS,
    ERROR_LIMIT,
}ERROR;

double minimum(double a, double b, double (*Function)(double), double epsilon, ERROR *error);
