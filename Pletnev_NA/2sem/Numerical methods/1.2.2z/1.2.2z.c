#include "1.2.2z.h"

double Intergarl(FR_R f, double a, double b, int n);
double Area_​​trapezoid(FR_R f, double x1, double x2);

double Area_​​trapezoid(FR_R f, double x1, double x2)
{
	double dx = x2 - x1;
	double m1 = (x1 + x2) / 2;
	double m2 = (x2 - x1) / (2 * sqrt(3));
	double f1 = (*f)(m1 - m2);
	double f2 = (*f)(m1 + m2);

	if ((f1 * f2) > 0)
	{
		return dx * (f1 + f2) / 2;
	}
	else
	{
		double m10 = (x1 + 0) / 2;
		double m01 = (0 - x1) / (2 * sqrt(3));
		double m02 = (0 + x2) / 2;
		double m20 = (x2 - 0) / (2 * sqrt(3));
		double f10 = (*f)(m10 - m01);
		double f01 = (*f)(m10 + m01);
		double f20 = (*f)(m02 - m20);
		double f02 = (*f)(m02 + m20);

		return fabs(x1) * (f01 + f10) / 2 + fabs(x2) * (f02 + f20) / 2;
	}
}


double Intergarl(FR_R f, double a, double b, int n)
{
	double sum = 0;
	double dx = (b - a) / n; 

	for (int i = 0; i < n; i++)
	{
		sum += Area_​​trapezoid(f, a + dx * i, a + dx * (i + 1));
	}

	return sum;
}


double trapezoid_method(FR_R f, double a, double b, double eps, Error* err)
{
	int limit = 1000000;
	double I1;
	double I2;
	int n = 1000;

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

	I1 = 0;
	I2 = Intergarl(f, a, b, n);

	while (fabs(I2 - I1) > eps)
	{
		I1 = I2;
		n *= 2;
		I2 = Intergarl(f, a, b, n);

		limit--;
		if (limit == 0)
		{
			*err = LIMIT_0;
			return I2;
		}
	}

	*err = GOOD;
	return I2;
}