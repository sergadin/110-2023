#include <stdio.h>
#include <math.h>
#include "teylor_cos.h"


double teylor_cos (double x, double eps)
{
	double cos = 1, x_val = x * x;
	int coef = 2, sign = -1, fact = 2;
	while (fabs( x_val / coef ) > eps)
	{
		cos = cos + (sign * (x_val / coef));
		coef = coef * (fact + 1) * (fact + 2);
		x_val = x_val * (x * x);
		sign = sign * -1;
		fact = fact + 2;
	}
	cos = cos + (sign * (x_val / coef));
	return cos;
}
