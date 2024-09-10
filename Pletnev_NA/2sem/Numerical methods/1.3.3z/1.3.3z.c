#include "1.3.3z.h"

double min_step(FR_R f, double a, double b, double eps, Error* err)
{
	int limit = 1000000;
	double dx;
	double xm = a;
	double fxm = (*f)(xm);
	double xi;
	double fxi;

	if (b < a)
	{
		*err = WRONG_AB;
		return 0;
	}

	if (fabs(b - a) < eps)
	{
		*err = WRONG_AB;
		return 0;
	}

	for (int n = 2; n < limit + 2; n++)
	{
		dx = (b - a) / n;

		for (int i = 0; i < n+1; i++)
		{
			xi = a + i * dx;
			fxi = (*f)(xi);
			if (fxi < fxm)
			{
				fxm = fxi;
				xm = xi;
			}
		}

		if (fabs(xm - a) < eps)
		{
			b = a + dx;
		}
		else if (fabs(xm - b) < eps)
		{
			a = b - dx;
		}
		else
		{
			a = xm - dx;
			b = xm + dx;
		}

		if (fabs(b - a) < eps)
		{
			*err = GOOD;
			return fxm;
		}
	}

	*err = LIMIT_0;
	return fxm;
}