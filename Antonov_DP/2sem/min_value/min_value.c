#include <stdio.h>
#include <math.h>
#include "integration.h"


double integrate(RRFun f, double a, double b, double eps, ERR *err)
{
	int count = 8; //количество отрезков, на которые разбивается отрезок
	double length, f_start, f_end, start, end, prev_integr = f(a)*(b - a), curr_integr;
	if (a > b) 
	{ 
		*err = E_IO;
		printf("ошибка, некорректно введён отрезок \n");
		return 0;
	}
	do
	{
		length = (b - a) / count;
		start = a;
		end = a + length;
		f_start = f(start);
		f_end = f(end);
		prev_integr = curr_integr;
		curr_integr = 0;
		for (int i = 0; i < count; i++)
		{
			curr_integr += ((f_start + f_end) * length) / 2;
			start = end;
			end += length;
			f_start = f_end;
			f_end = f(end);
		}
		count = count * 2;
	}
	while ((fabs(prev_integr - curr_integr) > eps) || (length > eps));
	return curr_integr;
}
