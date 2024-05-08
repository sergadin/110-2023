#include <stdio.h>
#include <math.h>
#include "find_root.h"

static int compRR(double a, double b, double eps);

static int compRR(double a, double b, double eps)
{
	if((a > 100000) || (b > 100000))
	{
		if (fabs(a - b) < eps * (a + b)) { return 0; }
		if (a > b) { return 1; }
		return -1;
	}
	if (fabs(a - b) < eps) { return 0; }
	if (a > b) { return 1; }
	return -1;
}


double find_root(RRFun f, double a, double b, double eps, ERR *err)
{
	int count = 1;
	double focus_point = a, prev = b, f_focus_point = 0, f_prev = 0, curr = 0;
	if (a > b) 
	{ 
		*err = E_NL;
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
		*err = E_SS;
		printf("значения функции на концах отрезка одного знака, ошибка \n");
		return 0;
	}
	if (fabs(f_focus_point) < eps) {return a;}
	if (fabs(f_prev) < eps) {return b;}
	curr = prev - (f_prev / (f_prev - f_focus_point)) * (prev - focus_point);
	while ((compRR(curr, prev, eps) != 0) && (count < 1000000))
	{
		prev = curr;
		f_prev = f(prev);
		curr = prev - (f_prev / (f_prev - f_focus_point)) * (prev - focus_point);
		count++;
	}
	if (count == 1000000) { printf ("ответ найден, но не с такой точностью \n"); }
	return curr;
}
