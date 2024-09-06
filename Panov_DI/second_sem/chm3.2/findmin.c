#include "findmin.h"

double findmin(RRFun f, double a, double b, double eps, error* err) {
	const double phi = 0.38196; // Коэффициент золотого сечения
	const int max_iterations = 1000;
	int iterations = 0;
	double x1, x2, f_x1, f_x2;

	// Проверка на корректность интервала
	if (a > b) {
		*err = INVALID_INTERVAL;
		return -1;
	}

	// Инициализация точек x1 и x2 по методу золотого сечения
	x1 = a + phi * (b - a);
	x2 = b - phi * (b - a);
	f_x1 = f(x1);
	f_x2 = f(x2);

	while ((fabs(f_x1 - f_x2) > eps) ||
		(fabs(f_x1 - f_x2) > eps * fabs(f_x1 + f_x2) / 2)) {

		if (f_x1 < f_x2) {
			b = x2;
			x2 = x1;
			x1 = a + phi * (b - a);
			f_x2 = f_x1;
			f_x1 = f(x1);
		}
		else {
			a = x1;
			x1 = x2;
			x2 = b - phi * (b - a);
			f_x1 = f_x2;
			f_x2 = f(x2);
		}

		iterations++;
		if (iterations >= max_iterations) {
			*err = I_LIMIT;
			return -1;
		}
	}

	printf("Минимум: %lf\n", f_x1);
	*err = OK;
	return f_x1;
}
