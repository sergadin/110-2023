#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "4.taylor_cos.h"


static double period(double x) { // уменьшаем значение икса с учётом периода косинуса (хочу работать с иксом от 0 до 2pi)
	double kol_period; // количество периодов (косинуса) в числе х
	double pi = M_PI; // число пи
	
	kol_period = floor(fabs(x) / (2 * pi)); // floor(y) возвращает наибольшее целое число, которое не больше, чем y
	x = fabs(x) - 2 * pi * (kol_period);
	
	return x;
}


// функция считает значение косинуса в точке, используя формулу тейлора

double count_taylor_cos(double x, double eps, error *err) {
	double res = 0; // посчитанное значение косинуса
	double sum = 1; // слагаемые ряда тейлора
	int iter = 0; // количество итераций
	int limit = 1000000; //максимальное количество итераций
	*err = OK; // код ошибки
	
	x = period(x);
	
	while (iter <= limit) {
		res = res + sum;
		sum = sum * (-1) * pow(x, 2) / ((iter + 1) * (iter + 2));
		if (fabs(sum) < eps) {
			return res;
		}
		iter = iter + 2;
	}
	
	if (iter > limit) {
		*err = MORE_THAN_LIMIT;
		return -1;
	}
}