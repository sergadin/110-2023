#include "int_1.h"
#include <math.h>
#include <stdio.h>

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
		{SIN, 1, 4, 1.1939459},
		{SIN, 7, 5, 0.470240},
		{POLYNOM, 0, 4, 34.666667},
		{RATIO, 3, 5, 0.527007},
	};
	double eps = 0.00001;
	int n;
	int limit = 50;
	double automatic;
	
	for (int i=0; i<4; i++) {
		integral(entry[i], eps, limit);
		
		//fabs(n * C * (b-a)^2/n^2) < eps
		//n > fabs(C * (b-a)^2)/eps
		//константу опустим
		n = ceil((entry[i].b-entry[i].a)*(entry[i].b-entry[i].a)/eps);
		automatic = rect(entry[i].f, entry[i].a, entry[i].b, n);
		printf("Автоматическое дробление: %d - %lf\n\n", n, automatic);
	}
	
	return 0;
}
