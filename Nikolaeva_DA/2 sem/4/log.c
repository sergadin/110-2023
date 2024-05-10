#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "log.h"

double taylor_log(double x, double eps, Error *err) {
	double result, term;
	int sgn, limit;
	if (x <= 0 || x == 1)
	{
		*err = OGRAN;
		return -1;
		*err = OK;
	}
	if (eps <= 0) {
		*err = NO_EPS;
		printf("eps должно быть больше 0\n");
		return -1;
	}

	result = 0;
	term = 1;
	sgn = -1;
	limit = 10000;

	while (fabs(term) > eps && (limit > 0)) {
		term *= x / sgn;
		result += term;
		sgn *= -1;
	}
	if (limit == 0){
		*err = NO_LIMIT;
		return -1;
	}
	return result;
}
