#include <math.h>

double my_cos(double x, double eps);

/* 
Функция выдает значение косинуса в данной точке с указанной точностью. Для этого вычисляется ряд тейлора до момента, пока не будет достигнута нужная точность.

Параметры:
	x - аргумент косинуса
	eps - точность вычислений




