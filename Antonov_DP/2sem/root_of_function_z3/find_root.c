#include <stdio.h>
#include <math.h>
#include "find_root.h"


double find_root(RRFun f, double a, double b, double eps, int *err)
{
	int count = 1;
	double f_a = f(a), prev = b, f_prev = f(prev),  curr = 0;
	if (a > b) 
	{ 
		err = 1;
		return 0;
	}
	if ((f_a * f_curr) > 0)
	{
		err = 2;
		return 0;
	}
	if (fabs(f_a) < eps) {return a;}
	if (fabs(f_prev) < eps) {return b;}
	curr = prev - (f_prev / (f_prev - f_a)) * (prev - a);
	while (fabs(curr - prev) > eps)
	{
		prev = curr;
		f_prev = f(prev);
		curr = prev - (f_prev / (f_prev - f_a)) * (prev - a);
	}
	return curr;
}
