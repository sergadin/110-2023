#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "newton_method.h"

double first_derivative(RRFun f, double eps, double x);

double first_derivative(RRFun f, double eps, double x)
{
	double dx = eps / 1000;
	double df = (*f)(x + dx) - (*f)(x);

	return df / dx;
}

double newton_method(RRFun f, double a, double b, double eps, Error* err)
{
	int limit = 10000;
	int n = 0;
	double xi1;
	double xi2;
	double df;

	if (b < a)
	{
		*err = W_AB;
		return 0;
	}
	if (fabs((*f)(b)) < eps)
	{
		*err = W_AB;
		return 0;
	}
	
	if (fabs((*f)(a)) < eps)
	{
		*err = W_AB;
		return 0;
	}

	if (fabs(b - a) < eps)
	{
		*err = W_AB;
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
				*err = OK;
				return xi1;
			}
			else
			{
				*err = W_f;
				return xi2;
			}
		}

		xi2 = xi1 - (*f)(xi1) / df;

		if ((fabs((*f)(xi2)) < eps) || (fabs(xi2 - xi1) < eps))
		{
			if ((a < xi2) && (xi2 < b))
			{
				*err = OK;
				return xi2;
			}
		}

		xi1 = xi2;
		limit--;
		n++;
	}

	*err = LIMIT_0;
	return xi2;
}