#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "log.h"

double taylor_log(double x, double eps, Error *err) {
	if (x <= 0 || x == 1)
	{
		*err = OGRAN;
		printf("х должно быть больше 0 и не равно 1\n");
		return -1;
		*err = OK;
	}
	if (eps <= 0) {
		*err = NO_EPS;
		printf("eps должно быть больше 0\n");
		return -1;
	}

	double sum = 0;
	int n = 1;
	double temp = 1;
	while (fabs(temp) > eps) {
		temp = pow(-1, n + 1) * pow(x - 1, n) / n;
		sum += temp;
		n++;
	}
	return sum;
}
