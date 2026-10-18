#include "root_3.h"
#include <math.h>
#include <stdio.h>

typedef struct {
	R_Rfun f;
	double a;
	double b;
	double res;
} test;

static double SIN(double x) {
	return sin(x);
}

static double POLYNOM(double x) {
	return (x*x*x - x*x + 2*x - 6);
}

int main(void) {
	test entry[3] = {
		{SIN, 1, 4, 3.1415926535897},
		{SIN, 7, 5, 6.2831853071795},
		{POLYNOM, 1, 2, 1.776045322},
	};
	double answ, eps;
	int count;
	error err;

	eps = 0.000000001;
	
	for (int i=0; i<3; i++) {
		printf("%d : ",  i+1);
		count = 0;
		
		answ = root(entry[i].f, entry[i].a, entry[i].b, eps, &count, &err);
		if (err == LIMIT) {
			printf("Превышение лимита итераций(ии/ия)\n");
		}
		else if (err == SAME_SIGN) {
			printf("Границы с одним знаком\n");
		}
		else if (err == NO_FUNCTION) {
			printf("Ошибка функции\n");
		}
		else {
			printf("%lf - %d итераций(ии/ия)\n", answ, count);
			printf("   Нужный ответ - %lf\n", entry[i].res);
		}
	}
	
	return 0;
}
