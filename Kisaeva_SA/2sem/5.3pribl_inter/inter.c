#include "inter.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void interpolation(point* xy_points, int kol_p, point* int_points, int kol_i_p, double* inter_y, error* err) {
	*err = OK;
	double x; // координата х точки интерполяции
	double x0, x1, x2, y0, y1, y2, a1, a2, a0; // координаты точек, используемых при интерполяции
	double v0, v1, v2; // весовые коэффиценты
	int i; // будем использовать для ограничения определения отрезка, в который попадает точка интерполяции
	double d; // переменная для упорядочивания точек
	
	// упорядочивание точек по возрастанию в изнач функции
	for (int k = 0; k < kol_p; k++) {
		for (int t = k; t < kol_p; t++) {
			if (xy_points[k].x > xy_points[t].x){
				d = xy_points[k].x;
				xy_points[k].x = xy_points[t].x;
				xy_points[t].x = d;
			
				d = xy_points[k].y;
				xy_points[k].y = xy_points[t].y;
				xy_points[t].y = d;
			}
		}
	}
	// упорядочивание интерп-ых точек по возрастанию
	for (int k = 0; k < kol_i_p; k++) {
		for (int t = k; t < kol_i_p; t++) {
			if (int_points[k].x > int_points[t].x){
				d = int_points[k].x;
				int_points[k].x = int_points[t].x;
				int_points[t].x = d;
			
				d = int_points[k].y;
				int_points[k].y = int_points[t].y;
				int_points[t].y = d;
			}
		}
	}
	
	// проверка точек интерполяции на совпадение
	for (int k = 0; k < kol_i_p - 1; k++) {
		for (int s = k + 1; s < kol_i_p; s++) {
			if(int_points[k].x == int_points[s].x){
				*err = ERR_INTER_POINTS; 
				for (int h = 0; h < kol_i_p; h++) {
					inter_y[h] = int_points[h].y;
				}
				return;
			}
		}
	}
	
	//подсчёт значения функции в интерп-ой точке с помощью метода кусочно-квадратичной интерполяции
	for (int j = 0; j < kol_i_p; j++) {
		if ((int_points[j].x < xy_points[0].x ) || (int_points[j].x > xy_points[kol_p - 1].x)) {
			*err = OUTOFRANGE; // точка интерполяции вне отрезка
			for (int h = 0; h < kol_i_p; h++) {
				inter_y[h] = int_points[h].y;
			}
			return;
		}
		// определение отрезка, в который попадает точка интерполяции по х
		for (i = 1; i < kol_p; i++) {
			if (xy_points[i].x >= int_points[j].x){
				break;
			}
		}
		
		x = int_points[j].x; 
		
		// первые две ближайшие точки, используемые при интерполяции:
		x0 = xy_points[i - 1].x; 
		x1 = xy_points[i].x;
		y0 = xy_points[i - 1].y;
		y1 = xy_points[i].y;
		
		// третья точка, используемая при интерполяции:
		if (i < kol_p - 1) { 
			x2 = xy_points[i + 1].x;
			y2 = xy_points[i + 1].y;
		}
		else {  // если это оказалась последняя точка, то выбираем предпоследнюю
			x2 = xy_points[i - 1].x;
			y2 = xy_points[i - 1].y;
		}

		v0 = ((x - x1) * (x - x2)) / ((x0 - x1) * (x0 - x2));    
		v1 = ((x - x0) * (x - x2)) / ((x1 - x0) * (x1 - x2));
		v2 = ((x - x0) * (x - x1)) / ((x2 - x0) * (x2 - x1));
		
		inter_y[j] = y0 * v0 + y1 * v1 + y2 * v2;
	}
}






