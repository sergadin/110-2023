#include "rectanglemeth.h"

static double rectavg(RRFun func, double a, double b);      // Функция, вычисляющая значение 
static double rectavg(RRFun func, double a, double b) {     // площади прямоугольника(среднего)
	
	double integral = func((a + b) / 2) * (b - a);

	return integral;
}


double countintegral(RRFun f, double a, double b, int* i_num, error* err) {
	int n = 1, limit = 10000;
	double prev_integral, cur_integral, eps = 1e-7;
	*err = OK;

	if (b < a) {
		*err = WRONG_INTERVAL;
		return -1;
	}

	cur_integral = rectavg(f, a, b);

	while (1) {                                    // Алгоритм удвоения сетки:
		double h;
		(*i_num)++;
		prev_integral = cur_integral;
		cur_integral = 0;
		n *= 2;
		h = (b - a) / n;
		for (int i = 0; i < n; i++)
			cur_integral += rectavg(f, a + i * h, a + (i + 1) * h);

		if (fabs(cur_integral - prev_integral) < (eps * fmax(fabs(cur_integral), fabs(prev_integral)))) {
			break;
		}

		limit--;
		if (limit < 0) {
			*err = I_LIMIT_EXCEEDED;
			return -1;
		}

	}
	printf("Интеграл = %lf\n", cur_integral);
	return cur_integral;
}