#include "lagrangepolynom.h"

void interpolate(point* p, int n, point* i_p, int m, double* i_y, error* err) {
	*err = OK;
	for (int j = 0; j < m; j++) {
		double result = 0.0;
		for (int i = 0; i < n; i++) {
			double term = p[i].y;
			for (int k = 0; k < n; k++) {
				if (i != k) {
					term = term * (i_p[j].x - p[k].x) / (p[i].x - p[k].x);
				}
			}
			result += term;
		}
		i_y[j] = result;
	}
}
