#include "findroot.h"

double find_root(RRFun func, double left, double right, double tolerance, int* iterations, error* err_code) {
	double f_left, f_right, f_mid, midpoint[2];
	int index = 0, max_iterations = 10000;

	if (left > right) {
		*err_code = INVALID_INTERVAL;
		return -1;
	}

	*err_code = OK;

	f_left = func(left);
	f_right = func(right);

	midpoint[0] = left;
	midpoint[1] = right;

	if (f_left * f_right > 0) {
		*err_code = INVALID_FUNCTION;
		return -1;
	}

	if (fabs(f_left) < tolerance) {
		printf("Корень - %lf\n", midpoint[index]);
		return left;
	}

	if (fabs(f_right) < tolerance) {
		printf("Корень - %lf\n", midpoint[index]);
		return right;
	}

	for (*iterations = 1; fabs(midpoint[1] - midpoint[0]) > tolerance; (*iterations)++) {
		index = !index;
		midpoint[index] = (left * f_right - right * f_left) / (f_right - f_left);
		f_mid = func(midpoint[index]);

		if (fabs(f_mid) < tolerance) {
			printf("Корень - %lf\n", midpoint[index]);
			return midpoint[index];
		}
		if (f_mid * f_left > 0) {
			left = midpoint[index];
			f_left = f_mid;
		}
		else {
			right = midpoint[index];
			f_right = f_mid;
		}

		max_iterations--;
		if (max_iterations < 0) {
			*err_code = I_LIMIT;
			return -1;
		}
	}

	printf("Корень - %lf\n", midpoint[index]);
	return midpoint[index];
}
