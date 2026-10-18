#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "log.h"

struct testing {
	double x;
	double result;
	double eps;
};

int main(void) {
	double value;
	double x;
	double eps;
	int i;
	Error err;
	struct testing tests[3] = {
		{0.5, -0.693147, 0.000001}, 
		{0.4, -0.916291, 0.000001},
		{0.9, -0.105360, 0.000001} 
	};

	for (i = 0; i < 3; i++) {
		x = tests[i].x;
		eps = tests[i].eps;
		value = taylor_log(x, eps, &err); 
		printf("Тест %d\n Значение x: %lf; Ожидаемый результат: %lf\n", i + 1, tests[i].x, tests[i].result);
		printf(" ln(x): %lf\n", value);
		printf("logf : %.20f\n", logf(x));
	}

	return 0;
}

