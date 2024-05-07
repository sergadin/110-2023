#include<stdio.h>
#include <math.h>
#include "parabola.h"

static double max(double x, double y, double eps);
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
double min_parabolic( RRFun f, double a, double b, double eps, Error *err) {
	if (a > b){
		*err = NA_INTER;
		return -1;
	}
	*err = OK;
	while ((b - a) > (max(b, a, 1.0) * eps)) {
		double x1 = (a + b) / 2 - (b - a) / 4;
		double x2 = (a + b) / 2 + (b - a) / 4;

		double fx1 = (*f)(x1);
		double fx2 = (*f)(x2);

		if (fx1 < fx2) {
			b = (a + b) / 2;
		} else {
			a = (a + b) / 2;
		}
	}
	double fa = (*f)((a + b) / 2);
	printf("%lf Минимальное значение  \n", fa);
	return fa;
}    
