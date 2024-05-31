#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "1.1.2z.h"

double first_derivative(FR_R f, double eps, double x);

double first_derivative(FR_R f, double eps, double x)
{
	double dx = eps/1000;
	double df = (*f)(x + dx) - (*f)(x);

	return df / dx;
}

double newton_tangent_method(FR_R f, double a, double b, double eps, Error* err, int* c)
{
	int limit = 10000;
	int n = 0;
	double xi1;
	double xi2;
	double df;

	if (b < a)
	{
		*err = WRONG_AB;
		*c = 0;
		return 0;
	}

	if (fabs(b - a) < eps)
	{
		*err = WRONG_AB;
		*c = 0;
		return 0;
	}

	if (fabs((*f)(b)) < eps)
	{
		*err = WRONG_AB;
		*c = 0;
		return 0;
	}

	if (fabs((*f)(a)) < eps)
	{
		*err = WRONG_AB;
		*c = 0;
		return 0;
	}

	xi1 = b;
	xi2 = xi1;

	while (limit > 0)
	{

		df = first_derivative(f, eps, xi1);
		if (fabs(df) < eps)
		{
			if (fabs((*f)(xi1)) < eps)
			{
				*err = GOOD;
				*c = n;
				return xi1;
			}
			else
			{
				*err = WRONG_f;
				*c = n;
				return xi2;
			}
		}

		xi2 = xi1 - (*f)(xi1) / df;

		if ((fabs((*f)(xi2)) < eps) || (fabs(xi2 - xi1) < eps))
		{
			if ((a < xi2) && (xi2 < b))
			{
				*err = GOOD;
				*c = n;
				return xi2;
			}
		}

		xi1 = xi2;
		limit--;
		n++;
	}

	*err = LIMIT_0;
	*c = n;
	return xi2;
}