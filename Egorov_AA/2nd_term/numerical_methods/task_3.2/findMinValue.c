#include "findMinValue.h"

double findMinValue(RRFun f, double a, double b, double eps, error* err) {
	const double phi = 0.38196;      // Отношение, в котором отрезок разбивается
	int limit = 1000;               // Ограничение на количество итераций
	double f_x1, f_x2, x1, x2;

	if (a > b) {
		*err = WRONG_INTERVAL;       // Проверка ошибки неверного задания интервала 
		return -1;
	}

	x1 = a + phi * (b - a);
	x2 = b - phi * (b - a);
	f_x1 = (*f)(x1);
	f_x2 = (*f)(x2);

	while ((fabs(f_x1 - f_x2) > eps) || (fabs(f_x1 - f_x2) > eps * fabs(f_x1 + f_x2) / 2)) {

		if (f_x1 < f_x2) {
			b = x2;
			x2 = x1;
			x1 = a + phi * (b - a);
			f_x2 = f_x1;
			f_x1 = (*f)(x1);
		}
		else {
			a = x1;
			x1 = x2;
			x2 = b - phi * (b - a);
			f_x1 = f_x2;
			f_x2 = (*f)(x2);
		}

		limit--;
		if (limit <= 0) {               // Проверка ошибки на превышение количества итераций
			*err = I_LIMIT_EXCEEDED;
			return -1;
		}
	}

	printf("Minimum: %lf\n", f_x1);
	*err = OK;
	return f_x1;
}
