#include "calculateIntegral.h"

static double gaussQuad(RRFun f, double a, double b);      // Функция, вычисляющая значение 
static double gaussQuad(RRFun f, double a, double b) {     // квадратуры гаусса
	double integral = 0.5 * (b - a) * 
		(f(0.5 * (a + b - ((b - a) / sqrt(3)))) + f(0.5 * (a + b + ((b - a) / sqrt(3)))));
	return integral;
}


double calcInt(RRFun f, double a, double b, double eps, int* i_num, error* err) {
	int n = 1, limit = 10000;
	double prev_integral, cur_integral;
	*err = OK;

	if (b < a) {
		*err = WRONG_INTERVAL;
		return -1;
	}
	
	cur_integral = gaussQuad(f, a, b);
	while (1) {                                    // Алгоритм удвоения сетки:
		double h;                                  // Отрезок, на котором ищется интеграл,
		(*i_num)++;                                // делится на подотрезки, на каждом из
		prev_integral = cur_integral;              // которых ищется интеграл, пока мы не
		cur_integral = 0;                          // достигнем нужной нам точности.
		n *= 2;
		h = (b - a) / n;
		for (int i = 0; i < n; i++)
			cur_integral += gaussQuad(f, a + i * h, a + (i + 1) * h);

		if (fabs(cur_integral - prev_integral) < eps)
			break;

		limit--;
		if (limit < 0) {
			*err = I_LIMIT_EXCEEDED;
			return -1;
		}
		
	}
	printf("integral = %lf\n", cur_integral);
	return cur_integral;
}