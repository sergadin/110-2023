#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
	OK,
    INCORRECT_ARG,
}error;


double my_sin(double x, double eps,error *err);

