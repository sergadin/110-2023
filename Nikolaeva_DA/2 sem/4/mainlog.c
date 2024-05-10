#include <stdio.h>
#include <math.h>
#include "log.h"

struct testing 
{
	double x;
	double result;
	double eps;
};

int main(void)
{
	double value;
	double x;
	double result;
	double eps;
	Error err;
	struct testing tests[4] =
	{
		{0, -1, 0.00001},
		{0.5, -0.599999, 0.000001},
		{0.4, -0.482758, 0.000001},
		{0.9, -0.944751, 0.000001}
	};

	for(int i = 0; i < 4; i++)
	{
		x = tests[i].x;
		result = tests[i].result;
		eps = tests[i].eps;
		value = taylor_log(x, eps, &err);
		printf("Тест %d\n Значение x: %lf; Ожидаемый результат: %lf\n", i+1, tests[i].x, tests[i].result);
		printf(" ln(1+x): %lf\n", value);
	}

	return 0;
}
