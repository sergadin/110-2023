#include "min_3.h"
#include <math.h>

void min_dots(R_Rfun f, double *a, double *b, int n, double eps) {
	double min[2]; //положение минимума и его значение
	double dx; //шаг
	
	if (*b < *a) {
		dx = *a;
		*a = *b;
		*b = dx;
	}
	
	dx = (*b - *a)/n;
	
	min[0] = *b;
	min[1] = (*f)(*b);
	
	for (double i=*a; i<*b; i+=dx) {
		if ((*f)(i) < min[1]) {
			min[0] = i;
			min[1] = (*f)(i);
		}
	}
	
	if (fabs(min[0] - *a) < eps) {
		*b = *a + dx;
		return;
	}
	
	if (fabs(min[0] - *b) < eps) {
		*a = *b - dx;
		return;
	}
	
	*a = min[0] - dx;
	*b = min[0] + dx;
	
	return;
}

int min_search(R_Rfun f, double *a, double *b, double eps) {
	int n = 2;
	
	while ((fabs(*a - *b) > eps) && (n < 10000)) {
		min_dots(f, a, b, n, eps);
		n++;
	}
	
	if (fabs(*a - *b) > eps) {
		return -1;
	}
	
	return 0;
}
