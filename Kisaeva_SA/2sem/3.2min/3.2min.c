#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "3.2min.h"

static double max(double x, double y, double eps); // вычисление максимума


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


// Функция для вычисления приближённого значения минимума функции на отрезке методом золотого сечения
 
double find_minimum_golden_ratio(func f, double a, double b, double eps, error *err) {
	double phi = 0.5 * (1.0 + sqrt(5.0)); // постоянная золотого сечения
	double x1, x2; // переменные для промежуточных точек золотого сечения
	double fx1, fx2; // значения функции в промежуточных точках х1 и х2
	int limit = 1000000; //максимальное количество итераций
	double min; // найденная точка, в которой функция минимальна
	double fmin; // найденное значение минимума функции
	*err = OK; // код ошибки
	
	if (a > b) {
		*err = DATA_ERR;
		return -1;
	}
	
	x1 = (b - (b - a)/phi);
	x2 = (a + (b - a)/phi);
	fx1 = f(x1);
	fx2 = f(x2);
	
	while ((fabs(b - a) > (eps * max(a, b, 1.0))) && (limit > 0)) {
		if (fx1 > fx2) {
			a = x1;
			x1 = x2;
			fx1 = fx2;
			x2 = (a + (b - a)/phi);
			fx2 = f(x2);
		}
		else if (fx1 < fx2) {
			b = x2;
			x2 = x1;
			fx2 = fx1;
			x1 = (b - (b - a)/phi);
			fx1 = f(x1);
		}
		limit--;
		if (limit == 0) {
			*err = MORE_THAN_LIMIT;
			return -1;
		}	
	}
	
	min = (a + b)/2.0;
	fmin = f(min);
	return fmin; 	
}