#include "interpolationOfFunc.h"

void interpolate(point* p, int n, point* i_p, int m, double* interp_y, Er* error){
	*error = OK;
	double result;
	double x0, y0, x1, y1, x2, y2, x;
	
	for (int j = 0; j < m; j++){

		int i;                       // поиск точки
		for (i = 1; i < n; ++i) {
			if (p[i].x >= i_p[j].x)
				break;
		}
		
		x0 = p[i - 1].x;  // узлы
		x1 = p[i].x; 
		y0 = p[i - 1].y;
		y1 = p[i].y;
		x = i_p[j].x;

		if(i < n - 1){          // вычисление значений
			x2 = p[i + 1].x;
			y2 = p[i + 1].y;
		}
		if(i == n - 1){
		    x2 = p[i - 1].x;
			y2 = p[i - 1].y;
		}
		
		double L0 = ((x - x1) * (x - x2)) / ((x0 - x1) * (x0 - x2));     
		double L1 = ((x - x0) * (x - x2)) / ((x1 - x0) * (x1 - x2));
		double L2 = ((x - x0) * (x - x1)) / ((x2 - x0) * (x2 - x1));

		result = y0 * L0 + y1 * L1 + y2 * L2;
		
		interp_y[j] = result;
	}
}