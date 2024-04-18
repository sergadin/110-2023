#include <stdio.h>
#include <math.h>
#include "find_root.h"


double find_root(RRFun f, double a, double b, double eps, int *err)
{
	int count = 1;
	double focus_point = a, prev = b, f_focus_point = 0, f_prev = 0, curr = 0;
	if (a > b) 
	{ 
		*err = 1;
		printf("отрезок неправильно задан a > b \n");
		return 0;
	}
	if (f(a) < 0) 
	{
		focus_point = b;
		prev = a;
	}
	f_focus_point = f(focus_point);
	f_prev = f(prev);
	if ((f_focus_point * f_prev) > 0)
	{
		*err = 2;
		printf("значения функции на концах отрезка одного знака, ошибка \n");
		return 0;
	}
	if (fabs(f_focus_point) < eps) {return a;}
	if (fabs(f_prev) < eps) {return b;}
	curr = prev - (f_prev / (f_prev - f_focus_point)) * (prev - focus_point);
	while (fabs(curr - prev) > eps)
	{
		prev = curr;
		f_prev = f(prev);
		curr = prev - (f_prev / (f_prev - f_focus_point)) * (prev - focus_point);
	}
	return curr;
}
