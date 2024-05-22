#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "find_min.h"

typedef struct
{ // структура для проведения тестов функции
	Rfun f;
	double a;
	double b;
	double eps;
	Error error;
} TestCase;

double linear_function(double x)
{
	return (-12) * x;
}

double parabola(double x)
{
	return 3 * x * x - 5 * x - 4;
}

int main(void)
{
	double result; // результат выполнения основной функции
	Error error;   // код ошибки основной функции
	double eps = 1e-5;

	TestCase tests[] = {
		{linear_function, -1, 1.5, eps, OK},
		{cos, -10, 10, eps, OK},
		{parabola, -4, 10, eps, OK},
	};

	for (int i = 0; i < 3; i++)
	{
		result = find_min(tests[i].f, tests[i].a, tests[i].b, tests[i].eps, &error);
		if (error != tests[i].error)
		{
			printf("Тест %d не пройден, результат: %lf\n", i + 1, result);
		}
		else if (error == OK)
		{
			printf("Тест %d пройден, минимум функции %lf\n", i + 1, result);
		}
		else if (error == OP_LIMIT)
		{
			printf("В тесте %d превышен предел числа операций, приблизительный минимум функции: %lf\n", i + 1, result);
		}
	}

	return 0;
}
