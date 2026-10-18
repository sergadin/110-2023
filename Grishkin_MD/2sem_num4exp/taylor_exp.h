#include <stdio.h>
#include <math.h>

typedef enum {
	OK,
	LIM,    //  Превышен лимит итераций
} error;

error error_code;

double taylor_exp(double x, double eps);
