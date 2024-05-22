#include <stdio.h>
#include <math.h>
#include "min_value.h"

static int compRR(double a, double b, double eps);

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MAX3(a, b, c) MAX(MAX((a), (b)), (c))

static int compRR(double a, double b, double eps)
{
        if (fabs(a - b) < eps * MAX3(a, b, 1))
	{
		return 0;
	}
	if (a > b)
	{
		return 1;
	}
	return -1;
}

static double min_value_parab(double x1, double y1, double x2, double y2, double x3, double y3, double eps);

static double min_value_parab(double x1, double y1, double x2, double y2, double x3, double y3, double eps)
{
	double a, b, c;
	if (compRR(y1, y3, eps) == 0) 
	{
		if (y1 < y2)
		{
			return y1;
		}
		return y2;
	}
	if ((compRR(y1, y2, eps) != 1) && (compRR(y1, y3, eps) != 1))
	{
		return y1;
	}
	if ((compRR(y3, y2, eps) != 1) && (compRR(y3, y1, eps) != 1))
        {
                return y3;
        }
	a = ((y1 - y2) * (x1 - x3) - (y1 - y3) * (x1 - x2)) / ((x1 - x2) * (x1 - x3) * (x2 - x3));
	b = (y1 - y2) - a * (x1 + x2);
	c = y1 - (a * x1 * x1) - (b * x1);
	return ((4 * a * c) - (b * b)) / (4 * a);
}


double min_value(RRFun f, double a, double b, double eps, ERR *err)
{
	double prev, f_prev, curr, f_curr, a1 = a, b1 = b, a2, b2, mid, f_mid, result, min_par, d;
	int n = 10;
	if (a > b)
	{
		printf("a > b неправильно введён отрезок \n");
		*err = E_IO;
		return 0;
	}
	while(compRR(a1, b1, eps) != 0)
	{
		d = (b1 - a1) / n;
		curr = a1;
		f_curr = f(curr);
		result = f_curr;
		a2 = a1;
		b2 = a1 + d;
		for (int i = 0 ; i < n; i++)
		{
			prev = curr;
			f_prev = f_curr;
			mid = curr + (d / 2);
			f_mid = f(mid);
			curr = curr + d;
			f_curr = f(curr);
			min_par = min_value_parab(prev, f_prev, mid, f_mid, curr, f_curr, eps);
			if (min_par < result)
			{
				result = min_par;
				a2 = prev;
				b2 = curr;
			}
		}
		a1 = a2;
		b1 = b2;
	}
	return result;
}
