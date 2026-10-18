#define _USE_MATH_DEFINES
#define pi M_PI
#define e M_E
#include <math.h>
#include <stdio.h>
#include "taylor_log.h"



//¬спомогательна€ структура дл€ проверки
typedef struct
{
	double x;	// аргумент
	double eps;	// погрешность
	Error err;	// адрес ошибки
	double lnx0;	// точный ответ

} BoxTest;

int main(void)
{
	Error err;
	double lnx;
	int n_tests;

	BoxTest tests[] = {
		{0, 0.0001, WRONG_x, 0},
		{-2, 0.0001, WRONG_x, 0},
		{0.5, 0.000001, GOOD, log(0.5)},
		{exp(-1), 0.000001, GOOD, -1},
		{1, 0.0001, GOOD, 0},
		{2, 0.0001, GOOD, log(2)},
		{2, 0.00000001, GOOD, log(2)},
		{e, 0.0001, GOOD, 1},
	};

	n_tests = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < n_tests; i++)
	{
		lnx = taylor_log(tests[i].x, tests[i].eps, &err);

		printf("Tht test %d ", i + 1);

		if (err != tests[i].err)
		{
			printf("failed\n");
		}
		else if (err == WRONG_x)
		{
			printf("has been verified\n");
		}
		else
		{
			printf("has been verified\n");
			printf("The difference between the found answer and the exact one is '%f'\n", fabs(lnx - tests[i].lnx0));
		}
	}

	return 0;
}