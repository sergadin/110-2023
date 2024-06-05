#include "int_1.h"
#include <math.h>
#include <stdio.h>

typedef struct {
	R_Rfun f;
	double a;
	double b;
	double res;
} test;

static double SIN(double x) {
	return sin(x);
}

static double POLYNOM(double x) {
	return (x*x*x - x*x + 2*x - 6);
}

static double RATIO(double x) {
	return (x - 1)/(x*x - 4);
}

int main(void) {
	test entry[4] = {
		{SIN, -1, 0, 1.1939459},
		{POLYNOM, 0, 4, 34.666667},
		{RATIO, 3, 5, 0.527007},
		{RATIO, 1, 3, INFINITY},
	};
	double eps = 0.00001;
	int n;
	ERROR error;
	double answ;
	
	for (int i=0; i<4; i++) {
		printf("%d : ", i+1);
		
		error = 0;
		answ = integral(entry[i].f, entry[i].a, entry[i].b, eps, &error);
		
		if (error == 1) {
			printf("Ошибка (превышен лимит операций)\n");
		}
		else {
			printf("Итог - %lf, нужно %lf\n", answ, entry[i].res);
		}
		
	}
	
	return 0;
}
