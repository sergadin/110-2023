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
	double eps = 0.00001;
	
	for (int i=0; i<3; i++) {
		if (min_search(entry[i].f, &entry[i].a, &entry[i].b, eps) == -1) {
			printf("Превышен лимит итераций\n");
		}
		else {
			printf("%lf\n", entry[i].a);
		}
	}
	
	return 0;
}
