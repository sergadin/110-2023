#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "polygon.h"

/*	Parameters: 
 *			   f - The real function
 *		       à - The left border of the intgral. Must be less then the right one.
 *             b - The right border of the intgral. Must be greater then the left one.
 *             n - The number of the subsegments in the partition
 *             *error_code - Expected errors
 */

static double max(double x, double y, double epsilon);
static double max(double x, double y, double epsilon) 
{
	double max_1;
	if (x > y) 
	{
		max_1 = x;
	}
	else 
	{
		max_1 = y;
	}
	if (epsilon > max_1) 
	{
		return epsilon;
	}
	return max_1;
}

double integrate_n(RRFun f, double a, double b, int n);
double integrate_n(RRFun f, double a, double b, int n) 
{
	double h; // Subsegment of the partition
	double x, y;
	double result = 0;

	h = (b - a) / n;

	for (int i = 0; i < n; i++) 
	{
		x = a + h * i;
		y = a + h * (i + 1);
		result += (f((x + y) / 2)) * h;
	}
	return result;
}

double Integrate(RRFun f, double a, double b, double epsilon, Error *error_code) 
{
	double h = (b - a); // Initial length of the segment
	double I; // Initial approximation of the integral
	double Inew; // New approximation of the integral
	double limit = 1000; // The limit of iterations
	int n = 1024; // The number of the subsegments in the partition

	if (a >= b) // Wrong order
	{
		*error_code = WRONG_ORDER;
		return -1;
	}

	Inew = integrate_n(f, a, b, n);
	n = 2048;

	while (fabs(Inew - I) > (max(Inew, I, 1.0) * epsilon))
	{
		I = integrate_n(f, a, b, n);
		Inew = I;
		n = 2 * n;

		limit -= 1;
		if (limit <= 0)
		{
			*error_code = ITERATION_LIMIT_EXCEEDED;
			return I;
		}
	}
	*error_code = OK;
	return I;
}