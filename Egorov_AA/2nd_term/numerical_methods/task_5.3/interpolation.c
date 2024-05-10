#include "interpolation.h"

void interpolate(point* p, size_t n, point* i_p, size_t m, double* interp_y, error* err) {
	*err = OK;
	for (int j = 0; j < m; j++) {
		double x2, y2;
		// Поиск отрезка, в который попадает x
		int i;
		for (i = 1; i < n; ++i) {
			if (p[i].x >= i_p[j].x)
				break;
		}

		// Вычисление значения на отрезке с помощью кусочно-квадратичной интерполяции
		if (i < n - 1) {
			x2 = p[i + 1].x;
			y2 = p[i + 1].y;
		}
		else {
			// Если последняя точка, то выбираем предпоследнюю
			x2 = p[i - 1].x;
			y2 = p[i - 1].y;
		}

		double L0 = ((i_p[j].x - p[i].x) * (i_p[j].x - x2)) / ((p[i - 1].x - p[i].x) * (p[i - 1].x - x2));
		double L1 = ((i_p[j].x - p[i - 1].x) * (i_p[j].x - x2)) / ((p[i].x - p[i - 1].x) * (p[i].x - x2));
		double L2 = ((i_p[j].x - p[i - 1].x) * (i_p[j].x - p[i].x)) / ((x2 - p[i - 1].x) * (x2 - p[i].x));

		double result = p[i - 1].y * L0 + p[i].y * L1 + y2 * L2;

		interp_y[j] = result;
	}
}
