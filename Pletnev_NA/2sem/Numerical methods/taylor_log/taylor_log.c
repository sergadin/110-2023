#define _USE_MATH_DEFINES
#define pi M_PI
#define e M_E
#include "taylor_log.h"

double taylor_log(double x, double eps, Error* err)
{
	int limit = 100000;
	double x1 = x - 1;
	double lnx = 0;
	double xi = -1;

	if ((fabs(x) < eps) || (x < 0))
	{
		*err = WRONG_x;
		return 0;
	}

	if (x > e)
	{
		*err = WRONG_x;
		return 0;
	}

	for (int i = 1; i < limit + 1; i++)
	{
		xi *= - x1 / i;
		lnx += xi;

		if (fabs(xi) < eps)
		{
			*err = GOOD;
			return lnx;
		}
	}

	*err = LIMIT_0;
	return lnx;
}