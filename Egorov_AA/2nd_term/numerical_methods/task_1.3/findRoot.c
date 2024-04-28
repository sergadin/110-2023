#include "findRoot.h"

double findRoot(RRFun f, double a, double b, double eps, int* iteration_num, error* err) {

	double f_a, f_b, f_c, c[2];
	int i = 0, limit = 10000;

	if (a > b) {
		*err = WRONG_INTERVAL;
		return -1;
	}

	*err = OK;

	f_a = (*f)(a);
	f_b = (*f)(b);

	c[0] = a;
	c[1] = b;

	if (f_a * f_b > 0) {
		*err = WRONG_FUNCTION;
		return -1;
	}

	if (fabs(f_a) < eps) {
		printf("Корень - %lf\n", c[i]);
		return a;
	}

	if (fabs(f_b) < eps) {
		printf("Корень - %lf\n", c[i]);
		return b;
	}

	for (*iteration_num = 1; fabs(c[1] - c[0]) > eps; (*iteration_num)++) {
		i = !i;
		c[i] = (a * f_b - b * f_a) / (f_b - f_a);
		f_c = (*f)(c[i]);

		if (fabs(f_c) < eps) {
			printf("Корень - %lf\n", c[i]);
			return c[i];
		}
		if (f_c * f_a > 0) {
			a = c[i];
			f_a = f_c;
		}
		else {
			b = c[i];
			f_b = f_c;
		}
		
		limit--;
		if (limit < 0) {
			*err = I_LIMIT_EXCEEDED;
			return -1;
		}
	}

	printf("Корень - %lf\n", c[i]);
	return c[i];
}