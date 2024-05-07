#include "interpolation.h"

void interpolate(point* p, size_t n, point* i_p, size_t m, double* interp_y, error* err) {
	double a, b, c;
	*err = OK;

	// Interpolate for each interval
	for (int i = 1; i < n; i++) {
		// Calculate coefficients of the quadratic polynomial
		a = (p[i - 1].y - p[i].y + p[i - 1].x * (p[i].y - p[i + 1].y) + p[i].x * (p[i + 1].y - p[i - 1].y)) /
			((p[i - 1].x - p[i].x) * (p[i - 1].x - p[i + 1].x));
		b = (p[i].y - p[i - 1].y + p[i].x * (p[i - 1].y - p[i + 1].y) + p[i - 1].x * (p[i + 1].y - p[i].y)) /
			((p[i].x - p[i - 1].x) * (p[i].x - p[i + 1].x));
		c = p[i - 1].y - a * p[i - 1].x * p[i - 1].x - b * p[i - 1].x;

		// Interpolate within the interval
		for (int j = 0; j < m; j++) {
			if (i_p[j].x >= i_p[i - 1].x && i_p[j].x <= i_p[i].x) {
				interp_y[j] = a * i_p[j].x * i_p[j].x + b * i_p[j].x + c;
			}
		}
	}
}