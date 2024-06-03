#include "log.h"
#include <math.h>
#include <stdio.h>
	
int main(void) {
	double x;
	double answ;
	double eps = 0.00000001;
	
	printf("Напишите число в интервале (0; 2)\n");
	if (scanf("%lf", &x) != 1) {
		printf("Ошибка данных\n");
		return -1;
	}
	
	x--;
	if (fabs(x) > 1-eps) {
		printf("Ряд не сходится\n");
		return -1;
	}
	
	answ = LOG(x, eps);
	printf("Тейлор - %lf, встроенный - %lf", answ, log(x+1));
	
	return 0;
}
