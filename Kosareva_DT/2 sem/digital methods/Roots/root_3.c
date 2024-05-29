#include <stdio.h>
#include "root_3.h"
#include <math.h>

void root(R_Rfun f, double begin, double end, double eps, int count, double res) {
	double x, y, a, b;
	
	a = (*f)(begin);
	b = (*f)(end); //Значения на концах интервала
	
	if (a*b > eps) { //Один и тот же знак
		printf("Интервал не подходит\n");
		return;
	}
	
	//   (end - x)/(x - begin) = -b/a
	//   end - x = b*begin/a - x*b/a
	//   x*(a - b) = end*a - b*begin
	x = (end*a - b*begin)/(a - b); //Пересечение хорды с Ox
	y = (*f)(x);
	
	if (fabs(y) < eps) {
		printf("%lf - %d итераций. Нужный результат - %lf\n", x, count, res);
		return;
	}
	count++;
	
	if (y*a > 0) {
		root(f, x, end, eps, count, res);
	}
	else {
		root(f, begin, x, eps, count, res);
	}
	
	return;
}
