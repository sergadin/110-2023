#include <stdio.h>
#include <math.h>
#include "teylor_cos.h"


double teylor_cos (double x, double eps)
{
	double cos = 1, x_val = fabs(x), x_orig;
	int coef = 2, sign = -1, fact = 2, count = 1; 
	x_val = x_val - (((int)(x_val / (2 * M_PI))) * (2 * M_PI)); 	//из-за того, что cos периодична, вычисляем положительное значение x без периода
	if ((x_val > M_PI)) {x_val = x_val - (2 * M_PI); }	//вычисляем минимальное по модулю значение x когда cos равны
	x_orig = x_val;
	x_val = x_val * x_val;
	while ((fabs( x_val / coef ) > eps) && (count < 1000000))
	{
		cos = cos + (sign * (x_val / coef));
		coef = coef * (fact + 1) * (fact + 2);
		x_val = x_val * (x_orig * x_orig);
		sign = sign * -1;
		fact = fact + 2;
		count++;
	}
	cos = cos + (sign * (x_val / coef));
	if (count == 1000000) { printf("ряд расходится \n"); }
	return cos;
}
