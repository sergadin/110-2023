#include <math.h>
#include "int_1.h"


int are_equal(double a, double b, double eps) {
	a = fabs(a);
	b = fabs(b);
	if (a>b && a>1) {
		eps = a*eps;
	}
	else if (b>a && b>1) {
		eps = b*eps;
	}
	
	if (fabs(a - b) < eps) {
		return 1;
	}
	return 0;
}

double rect(R_Rfun f, double a, double b, int n) {
	double dx, i, summ;
	
	dx = (b - a)/n;
	summ = 0;
	
	if (b>a) {
		for (i=a; i<b; i+=dx) {
			summ += dx * (*f)(i);
		}
		return summ;
	}
	for (i=a; i>b; i+=dx) {
		summ += dx * (*f)(i);
		}
	return summ;
}

double integral(R_Rfun f, double a, double b, double eps, ERROR *err) {
	int n = 256;
	double res1, res2; //суммы с увеличением разбиения
	int limit = 15;
	
	*err = OK;
	
	res1 = rect(f, a, b, n);
	
	n *= 2;
	
	res2 = rect(f, a, b, n);
	
	while (are_equal(res1, res2, eps) == 0) {
		//printf("%d, %lf\n", n, res2);
		n *= 2;
		res1 = res2;
		res2 = rect(f, a, b, n);
		limit--;
		
		if (limit < 0) {
			*err = E_LIMIT;
			return res2;
		}
	}
	
	return res2;
}
	
