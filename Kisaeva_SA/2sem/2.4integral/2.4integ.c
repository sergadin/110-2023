#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "2.4integ.h"

static double max(double x, double y, double eps); // вычисление максимума
static double gauss_quadratute(func f, double a, double b); // вычисление квадратуры Гаусса


static double max(double x, double y, double eps) {
	double max_ch;
	if (x > y) {
		max_ch = x;
	}
	else if (y > x) {
		max_ch = y;
	}
	if (eps > max_ch) {
		max_ch = eps;
	}
	return max_ch;
}


static double gauss_quadratute(func f, double a, double b) {
	return ((b-a)/2.0) * ( (f(((a+b)/2.0) - ((b-a)/(2.0*sqrt(3.0))))) + (f(((a+b)/2.0) + ((b-a)/(2.0*sqrt(3.0))))) );
}


//Функция определяет приближённое значение интеграла функции на данном отрезке [a,b] 
// с заданной точностью eps  
// использует вычисление квадратуры Гаусса 
// использует алгоритм удвоения сетки

double integration_gauss(func f, double a, double b, double eps, error *err) {
	double cur_integ = 0, pred_integ = 0; // нынешний интеграл, предыдущий посчитанный интеграл
	double grid_step; // шаг сетки
	int limit = 1000000; //максимальное количество итераций
	int n = 1; // количество шагов сетки
	*err = OK; // код ошибки
	
	if (a > b) {
		*err = DATA_ERR;
		return -1;
	}
	
	grid_step = ((b - a)/n);
	for ( int i = 0; i < n ; i++) {
		pred_integ = pred_integ + gauss_quadratute(f, a + i*grid_step , a + (i+1)*grid_step);
	}
	n = n*2;
	grid_step = grid_step/2.0;
	for ( int i = 0; i < n ; i++) {
		cur_integ = cur_integ + gauss_quadratute(f, a + i*grid_step , a + (i+1)*grid_step);
	}
	
	while (fabs(cur_integ - pred_integ) > (eps * max(cur_integ, pred_integ, 1.0)) && (limit > 0)) {
		pred_integ = cur_integ;
		cur_integ = 0;
		n = n*2;
		grid_step = grid_step/2.0;
		for (int i = 0; i < n ; i++) {
			cur_integ = cur_integ + gauss_quadratute(f, a + i*grid_step , a + (i+1)*grid_step);
		}
		limit--;
	}
	
	if (limit == 0) {
		*err = MORE_THAN_LIMIT;
		return pred_integ;
	}

	return cur_integ;
}