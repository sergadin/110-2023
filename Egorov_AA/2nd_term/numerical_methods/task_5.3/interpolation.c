#include "interpolation.h"

void interpolate(point* p, size_t n, point* i_p, size_t m, double* interp_y, error* err) {
	*err = OK;
	for (int j = 0; j < m; j++) {
		double x2, y2;

		int i;                    // Поиск отрезка, в который попадает x
		for (i = 1; i < n; ++i) {
			if (p[i].x >= i_p[j].x)
				break;
		}
		
		double x0 = p[i - 1].x, x1 = p[i].x, 
		       y0 = p[i - 1].y, y1 = p[i].y,
		       x = i_p[j].x;

		if (i < n - 1) {          // Вычисление значения на отрезке с помощью кусочно-квадратичной интерполяции
			x2 = p[i + 1].x;
			y2 = p[i + 1].y;
		}
		else {                    // Если последняя точка, то выбираем предпоследнюю
			x2 = p[i - 1].x;
			y2 = p[i - 1].y;
		}

		double L0 = ((x - x1) * (x - x2)) / ((x0 - x1) * (x0 - x2));
		double L1 = ((x - x0) * (x - x2)) / ((x1 - x0) * (x1 - x2));
		double L2 = ((x - x0) * (x - x1)) / ((x2 - x0) * (x2 - x1));

		double result = y0 * L0 + y1 * L1 + y2 * L2;
		
		interp_y[j] = result;
	}
}
