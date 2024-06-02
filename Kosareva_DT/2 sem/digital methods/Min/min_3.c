#include "min_3.h"
#include <math.h>

typedef struct{
	double x;
	double y;
} dot;

double max(double a, double b, double c) {
	if (b > a) {
		a = b;
	}
	if (c > a) {
		a = c;
	}
	
	return a;
}

void min_dots(R_Rfun f, double *a, double *b, int n, double eps) {
	dot min; //положение минимума и его значение
	double dx; //шаг
	
	if (*b < *a) {
		dx = *a;
		*a = *b;
		*b = dx;
	}//Упорядочим края
	
	dx = (*b - *a)/n;
	
	min.x = *b;
	min.y = (*f)(*b);
	
	for (double i=*a; i<*b; i+=dx) {
		if ((*f)(i) < min.y) {
			min.x = i;
			min.y = (*f)(i);
		}
	}
	
	if (fabs(min.x - *a) < (eps * max(*a, min.x, 1))) {
		*b = *a + dx;
		return;
	}
	
	if (fabs(min.x - *b) < (eps * max(*b, min.x, 1))) {
		*a = *b - dx;
		return;
	}
	
	*a = min.x - dx;
	*b = min.x + dx;
	
	return;
}

double min_search(R_Rfun f, double a, double b, double eps, int *err) {
	int n = 2;
	
	while (fabs(a - b) > (eps * max(a, b, 1))) {
		min_dots(f, &a, &b, n, eps);
			n*=2;
		if (n > 100000000) {
			*err = 1;
			return -1;
		}
	}
	
	
	return (*f)(a);
}
