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
	double y, x;
	double x1, x2, fx1, fx2, fa, v_x, v_y, A, B;
	int limit = 10000;
	if (a > b){
		*err = NO_INTER;
		return -1;
	}
	*err = OK;
	while ((b - a) > (max(b, a, 1.0) * eps)) {
		x1 = (a + b) / 2 - (b - a) / 4;
		x2 = (a + b) / 2 + (b - a) / 4;

		fx1 = (*f)(x1);
		fx2 = (*f)(x2);

		if (fx1 < fx2) {
			b = (a + b) / 2;
		} else {
			a = (a + b) / 2;
		}
	}
	fa = (*f)((a + b) / 2);//минимум функции

	v_x = (a + b) / 2;
	v_y = (*f)(v_x);
	A = ((*f)(a) - v_y) / ((a - v_x) * (a - v_x));
	B = ((*f)(a) - v_y) / (a - v_x);

	for (double x = a; x <= b; x += 0.1) {
		y = A * (x - v_x) * (x - v_x) + v_y;
	}
	if (limit == 0){
        *err = NO_LIMIT;
        return 100000;
    }
	printf("%lf Минимальное значение параболы \n ",y);
	return y;
}

