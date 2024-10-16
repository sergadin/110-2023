#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "log.h"

double taylor_log(double x, double eps, Error *err) {
	double value = 0;
	int n = 1;
	double term = x - 1;//для log(x)
	int limit = 10000;
	*err = OK;
	if (x <= 0) {
		*err = OGRAN;
		return -1;
	}
	if (eps <= 0) {
		*err = NO_EPS;
		printf("eps должно быть больше 0\n");
		return -1;
	}
	while (fabs(term) >= eps) {
		value += term;
		n++;
		term = -term * (x - 1) * (n - 1) / n; // вычисляем следующий член с использованием предыдущего
		if (limit == 0) {
			*err = NO_LIMIT;
			return -1;
		}
	}
	return value;
}
