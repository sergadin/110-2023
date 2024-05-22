#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "kor.h"

static double max(double x, double y, double eps){
	double m_1;
	if (x > y){
		m_1 = x;
	}else{
		m_1 = y;
	}
	if (eps > m_1){
		return eps;
	}
	return m_1;
}
#define SECURITY_DEPTH 1000000

double chord_metod(RRFun f, double a, double b, double eps, int *max_iter, Error *err){
	double x_i, x_pred, f_xi, f_a = (*f)(a), f_b = (*f)(b); 
	int iter = 0;
	if(a > b) {
		*max_iter = 0;
		*err = NO_FUNC;
		return -1;
	}

	if(f_a * f_b > 0) {
		*max_iter = 0;
		*err = NO_FUNC;
		return -1;
	}
	x_i = a - ((f_a * (b-a)) / (f_b - f_a));
	x_pred = a;
	f_xi = (*f)(x_i);

	while((iter < SECURITY_DEPTH) && (fabs(x_i - x_pred) > (max(x_i, x_pred, 1.0) * eps))) {
		if (f_xi * f_b < 0) {
			a = x_i;
			f_a = f_xi;
		} else if (f_xi * f_a < 0) {
			b = x_i;
			f_b = f_xi;
		} else {
			*max_iter = iter;
			*err = NO_FUNC;
			return -1;
		}
		x_pred = x_i;
		x_i = a - ((f_a * (b-a)) / (f_b - f_a));
		f_xi = (*f)(x_i);
		iter++;
	}

	if (iter >= SECURITY_DEPTH) {
		*max_iter = iter;
		*err = NO_ITER;
		return -1;
	}
	printf("%lf\n", x_i);
	*max_iter = iter;
	*err = OK;
	return x_i;
}




