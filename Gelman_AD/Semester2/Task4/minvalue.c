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

double min(double x1, double x2, double x3);
double min(double x1, double x2, double x3) 
{
	if (x1 < x2 && x1 < x3) 
	{
		return x1;
	}
	else if (x2 < x3) 
	{
		return x2;
	}
	else 
	{
		return x3;
	}
}

double min_value(RRFun f, double a, double b, double epsilon, error* error_code)
{
	double x1, x2, x3;
	double x_min;
	double step; // The shredding step of the even net
	double x0; // The vertex of the parabola
	int limit = 1000; // The iterations limit

	if (a > b)
	{
		*error_code = WRONG_INTERVAL;
		return -1;
	}

	while (fabs(b - a) > epsilon)
	{
		step = (b - a) / 1000;
		x1 = a;
		x2 = a + step;
		x3 = a + 2 * step;

		while (x3 <= b)
		{
			if (f(x1) > f(x2) && f(x2) < f(x3))
			{
				break; // End of the while cycle
			}
			x1 = x2;
			x2 = x3;
			x3 += step;
		}

		x0 = 0.5 * (x1 + x3); // Calculating the coordinates of the vertex
		x_min = min(x1, x2, x3);

		if (f(x0) < f(x_min))
		{
			if (x0 < x_min)
			{
				b = x_min;
			}
			else
			{
				a = x_min;
			}
		}
		else
		{
			if (x2 < x_min)
			{
				a = x0;
			}
			else
			{
				b = x0;
			}
		}

		limit--;
		if (limit <= 0)
		{
			*error_code = ITERATION_LIMIT_EXCEEDED;
			return -1;
		}
	}
	*error_code = OK;
	x_min = 0.5 * (a + b);
	printf("Minimum of the function: %lf\n", f(x_min));
	return f(x_min); // min_value = f(x_min)
}