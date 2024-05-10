#include <stdio.h>
#include <math.h>
#include "integration.h"

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
	while ((compRR(curr_integr, prev_integr, eps) != 0) && (length > eps) && (count < 1000000));
	if ((length < eps) || (count > 1000000)) { printf("найден ответ, но не с требуемой точностью \n"); }
	return curr_integr;
}
