#include "integral.h"
#include <stdio.h>


typedef struct
{
	RRFun f;	
	double a;	
	double b;	
	double eps;	
	Error err;	
	double x;	

}TestCase;



static double square_trinomial(double x);
static double Const(double x);
static double exponent(double x);


static double Identical(double x)
{
	return x;
}

static double square_trinomial(double x)
{
	return x * x - 8 * x + 7;
}

static double Const(double x)
{
	return 2;
}

static double exponent(double x)
{
	return pow(2.71828, x);
}


int main(void)
{
	Error err;
	double x;
	int n_tests;
	const double pi = 3.141592;
	TestCase tests[] = {
		{sin, pi, -pi, 0.001, W_AB, 0},
		{sin, pi / 2, pi / 2, 0.001, W_AB, 0},
		{sin, -pi / 2, pi / 2, 0.001, OK, 0},
		{square_trinomial, 0, 4, 0.001, OK, 14.6},
		{exponent, 0, 4, 0.00001, OK, 53.5981},
		{exponent, 1, 3, 0.00001, OK, 2.3504}
	};


	for (int i = 0; i < 6; i++)
	{
		x = integral(tests[i].f, tests[i].a, tests[i].b, tests[i].eps, &err);

		if (err != tests[i].err)
		{
			printf("Тест %d не пройден\n", i + 1);
		}
		else if (err == W_AB)
		{
			printf("Тест %d пройден\n", i + 1);
		}
		else
		{
			printf("Тест %d не пройден\n", i + 1);
			printf("Тест %d пройден/ Погрешность составила %f\n", fabs(x - tests[i].x));
		}
	}

	return 0;
}