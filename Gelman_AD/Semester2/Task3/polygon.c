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

static double Integrate(RRFun f, double a, double b, double n);
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

// I(a, b, f) = ((b - a) / 2)(fa + fb);
static double Integrate(RRfun f, double a, double b, double n)
{
	double dx; // Subsegment of the partition
	double sum; // Integral sum
	dx = (b - a) / n;
	sum = (*f)(a) + (*f)(b);
	for (int i = 1; i < n; i++)
	{
		// sum += ???
	}
	sum = (sum * dx) / 2;
	return sum;
}


double polygon_method(RRFun f, double a, double b, double epsilon, Error* error_code) 
{
	double s1, s2, limit = 1000; // First & second integral sum respectfully
	int n = 1024;
	if (a >= b) // Wrong order
	{
		*error_code = WRNG_ORDER;
		return -1;
	}
	s1 = Integrate(f, a, b, n);
	n = 2048;
	while (fabs(s1 - s2) > (max(s1, s2, 1.0) * epsilon)) 
	{
		s2 = Integrate(f, a, b, n);
		s1 = s2;
		n = 2 * n;
		limit -= 1;
		if (limit <= 0) 
		{
			*error_code = ITERATION_LIMIT_EXCEEDED;
			return s2;
		}
	}
	*error_code = OK;
	return s2;
}