#include "newton_method.h"
#include <stdio.h>

typedef struct
{
	RRFun f;	
	double a;	
	double b;	
	double eps;	
	Error err;	
	double x;	

} TestCase;

double id(double x);
double square_trinomial(double x);

double id(double x)
{
	return x;
}

double square_trinomial(double x) 
{
	return x * x - 8 * x + 7;
}


int main(void)
{
	Error err;
	double x;
	const double pi = 3.141592653;

	TestCase tests[] = {
		{id, 0, -1, 0.001, W_AB, 0},
		{id, 0, 1, 0.001, W_AB, 0},
		{sin, -pi / 2, pi / 2, 0.001, W_f, 0},
		{sin, -pi / 4, pi / 4, 0.001, OK, 0},
		{square_trinomial, 0, 2, 0.00001, OK, 1},
		{square_trinomial, 2, 10, 0.00001, OK, 7},
		{id, -1, 4, 0.00001, OK, 0},
		{id, -1, 100000, 0.00001, OK, 0},
	};


	for (int i = 0; i < 8; i++)
	{
		x = newton_method(tests[i].f, tests[i].a, tests[i].b, tests[i].eps, &err);

		if (err != tests[i].err)
		{
			printf("Тест %d не пройден\n", i + 1);
		}
		else if (err == OK)
		{
			int ep = fabs(x - tests[i].x);
			printf("Тест %d пройден, Погрешность составила %lf\n", i + 1, ep);
		}
		else
		{
			printf("Тест %d пройден\n", i + 1);
		}
	}

	return 0;
}