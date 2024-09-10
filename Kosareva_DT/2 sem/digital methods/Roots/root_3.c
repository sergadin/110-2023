#include "root_3.h"
#include <math.h>
#include <stdio.h>

double root(R_Rfun f, double a, double b, double eps, int *count, error *err) {
	double x, y, fa, fb; //коо пересечения с Ох и значения на краях
	
	*err = OK;
	
	if (f == NULL) {
		*err = NO_FUNCTION;
		return INFINITY;
	}
	
	fa = (*f)(a);
	fb = (*f)(b); //Значения на концах интервала
	
	if (fa*fb > eps) { //Один и тот же знак
		*err = SAME_SIGN;
		if (fa < fb) {
			return fa;
		}
		return fb;
	}
	
	x = (b*fa - fb*a)/(fa - fb);
	y = (*f)(x);
	
	if (fabs(y) < eps) {
		return x;
	}
	
	(*count)++;
	if (*count > 100000) {
		*err = LIMIT;
		return -1;
	}
		
	if (y*fa > eps) {
		x = root(f, x, b, eps, count, err);
	}
	else {
		x = root(f, a, x, eps, count, err);
	}
	
	return x;
}
