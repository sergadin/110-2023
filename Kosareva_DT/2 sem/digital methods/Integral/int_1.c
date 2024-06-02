#include <math.h>
#include <stdio.h>
#include "int_1.h"

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

void integral(test entry, double eps, int limit) {
	int n = 2;
	double res1, res2; //суммы с увеличением разбиения
	
	res1 = rect(entry.f, entry.a, entry.b, n);
	
	n *= 2;
	
	res2 = rect(entry.f, entry.a, entry.b, n);
	
	while ((fabs(res1 - res2) > eps) && (limit > 0)) {
		//printf("%d, %lf\n", n, res2);
		n *= 2;
		res1 = res2;
		res2 = rect(entry.f, entry.a, entry.b, n);
		limit--;
	}
	
	if (fabs(res1 - res2) > eps) {
		printf("Превышен лимит итераций");
		return;
	}
	
	printf("Дробление - %d, результат - %lf, верный ответ - %lf\n", n, res2, entry.res);
	
	return;
}
	
