#include"integral.h"

double partition(RRFun f, double a, double b, int n);
double area(RRFun f, double x1, double x2);

double area(RRFun f, double x1, double x2)
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


double partition(RRFun f, double a, double b, int n)
{
	double sum = 0;
	double dx = (b - a) / n;

	for (int i = 0; i < n; i++)
	{
		sum += area(f, a + dx * i, a + dx * (i + 1));
	}

	return sum;
}


double integral(RRFun f, double a, double b, double eps, Error* err)
{
	int limit = 100000;
	double I1;
	double I2;
	int n = 1000;

	if (b < a)
	{
		*err = W_AB;
		return 0;
	}

	if (fabs(b - a) < eps)
	{
		*err = W_AB;
		return 0;
	}

	I1 = 0;
	I2 = partition(f, a, b, n);

	while ((fabs(I1 - I2) > fmax(I1, fmax(I2, 1.0)) * eps))
	{
		I1 = I2;
		n *= 2;
		I2 = partition(f, a, b, n);

		limit--;
		if (limit == 0)
		{
			*err = LIMIT_0;
			return I2;
		}
	}

	*err = OK;
	return I2;
}