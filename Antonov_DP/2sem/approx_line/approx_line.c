#include <stdio.h>
#include <math.h>
#include "approx_line.h"

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

int approx_line(double *x, double *y, double *a, double *b, int len, double eps, ERR *err)
{
	double a00 = len, a01 = 0, a10 = 0, a11 = 0, b0 = 0, b1 = 0;
	for (int i = 0; i < len; i++)
	{
		a01 += x[i];
	}
	a10 = a01;
	for (int i = 0; i < len; i++)
        {
                a11 += x[i] * x[i];
        }
	for (int i = 0; i < len; i++)
        {
                b0 += y[i];
        }
	for (int i = 0; i < len; i++)
        {
                b1 += y[i] * x[i];
        }
	if (compRR(a01 * a10, a00 * a11, eps) == 0)
	{
		*a = 100000;
		*b = 0;
		return 0;
	}
	*a = ((b0 * a10) - (b1 * a00)) / ((a01 * a10) - (a00 * a11));
	*b = (b0 - (a01 * (*a))) / a00;
	return 0;
}
