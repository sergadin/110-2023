#include "findMinValue.h"

double findMinValue(RRFun f, double a, double b, double eps, error* err) {
	const double phi = 0.382;
	while ((fabs(b - a) > eps * fabs(a + b) / 2) || (fabs(b - a) > eps)) {
		double x1, x2;

		x1 = a + phi * (b - a);
		x2 = b - phi * (b - a);

		if ((*f)(x1) < (*f)(x2)) {
			b = x2;
		}
		else {
			a = x1;
		}

	}
	printf("Minimum: %lf\n", (a + b) / 2);
	*err = OK;
	return (a + b) / 2;
}