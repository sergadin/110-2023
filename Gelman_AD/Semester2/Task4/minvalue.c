#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "minvalue.h"

/*
Parameters:
function — function pointer
a, b - borders of the segment
epsilon — specified accuracy
error_code - expected error
*/

double min_value(RRFun f, double a, double b, double epsilon, error* error_code);
double min_value(RRFun f, double a, double b, double epsilon, error* error_code)
{
	int step = 2; // The shredding step of the even net
	int limit = 1000; // The iterations limit
	double dx = 0;
	double ai = 0;
	double f_ai = 0;
	double x_min;
	double min;

	if (a > b)
	{
		*error_code = WRONG_INTERVAL;
		return -1;
	}

	if (f(a) > f(b))
	{
		x_min = b;
		// min = f(x_min) = f(b);
	}
	else // (f(b) < f(a))
	{
		x_min = a;
		// min = f(x_min) = f(a);
	}

	while (fabs(b - a) > epsilon && step < limit)
	{
		dx = (b - a) / step;

		for (int i = 0; i <= step; i++)
		{
			ai = a + i * dx;
			f_ai = f(ai);
			if (f(ai) < f(x_min))
			{
				min = f(ai);
				x_min = ai;
			}
		}

		if (fabs(x_min - a) < epsilon)
		{
			b = a + dx;
		}

		if (fabs(x_min - b) < epsilon)
		{
			a = b - dx;
		}

		if (fabs(x_min - a) >= epsilon && fabs(x_min - b) >= epsilon)
		{
			a = x_min - dx;
			b = x_min + dx;
		}

		step++;
		limit--;

		if (limit <= 0)
		{
			*error_code = ITERATION_LIMIT_EXCEEDED;
			return -1;
		}
	}
	*error_code = OK;
	printf("Minimum of the function: %lf\n", f(x_min));
	return f(x_min); // min_value = f(x_min)
}