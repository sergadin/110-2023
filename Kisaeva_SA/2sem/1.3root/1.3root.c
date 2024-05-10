#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "1.3root.h"

static int sign(double x); // функция определения знака
static double max(double x, double y, double eps); // функция определения максимума из трёх чисел


static double max(double x, double y, double eps){
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
 
static int sign(double x){
	if (x > 0) {
		return 1;
	}
	return -1;
}


// с помощью метода хорд функция ищет приближенное значение корня функции f(x)

double chord_method(func f, double a, double b, double eps, error *err, int *kol_iters){
	double x, fx; // точка пересечения с осью ох, значение функции в этой точке
	double x_pred; // предыдущая точка пересечения с осью ох
	double fa = (*f)(a), fb = (*f)(b); // значения функции на концах отрезка
	int iters = 0; // количество итераций
	int limit_iters = 1000000; // максимальное допустимое количество итераций
	*err = OK; // код ошибки

	if (a > b) {
		*err = DATA_ERR;
		return -1;
	}
	if ((sign(fa)*sign(fb)) > 0) {
		*err = NO_ROOT;
		return -1;
	}
	
	x = a - ((fa * (b-a)) / (fb - fa));
	fx = (*f)(x);
	x_pred = a;
	
	while(fabs(x - x_pred) > ((max(x, x_pred, 1.0) * eps)) && (limit_iters > 0)) {
		if ((sign(fx) * sign(fb)) < 0) {
			a = x;
			fa = fx;
		}
		else if ((sign(fx) * sign(fa)) < 0) {
			b = x;
			fb = fx;
			}
		else {
			*err = NO_ROOT;
			return -1;
		}
		x_pred = x;
		x = a - ((fa * (b-a)) / (fb - fa));
		fx = (*f)(x);
		limit_iters--;
		iters++;
		}
		
		if (limit_iters == 0){
			*err = NO_ROOT;
			return -1;
		}
		*kol_iters = iters; 
		return x;
}