#include "min_3.h"
#include <math.h>
#include <stdio.h>

typedef struct {
	R_Rfun f;
	double a;
	double b;
} test;
	
static double SIN(double x) {
	return sin(x);
}

static double PARABOLA(double x) {
	return (3*x*x - 2*x + 6);
}

int main(void) {
	test entry[3] = {
		{SIN, 1.6, 6},
		{SIN, 7, 5},
		{PARABOLA, -100, 100}
	};
	int error;
	double eps = 0.0000001;
	double min;
	
	for (int i=0; i<3; i++) {
		error = 0;
		min = min_search(entry[i].f, entry[i].a, entry[i].b, eps, &error);
		if (error == 1) {
			printf("Ошибка\n");
		}
		else {
			printf("%lf\n", min);
		}
	}
	
	return 0;
}
