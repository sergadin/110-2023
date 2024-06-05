#define _USE_MATH_DEFINES
#define pi M_PI
#define e M_E
#include "1.3.3z.h"
#include <stdio.h>

//Вспомогательная структура для проверки
typedef struct
{
	FR_R f;	// функция для поиска 0 функции
	double a;	// начало отрезка
	double b;	// конец отрезка
	double eps;	// погрешность
	Error err;	// адрес ошибки
	double x;	// точный ответ

} BoxTest;

//Вспомогательная функция для тестирования: квадратичная 
static double Polynomial2(double x);
//Вспомогательная функция для тестирования: константа
static double Const(double x);

static double Polynomial2(double x)
{
	return (x - 3) * (x - 3) + 5;
}

static double Const(double x)
{
	return 6;
}


int main(void)
{
	Error err;
	double x;
	int n_tests;

	BoxTest tests[] = {
		{sin, pi / 2, -pi / 2, 0.001, WRONG_AB, 0},
		{sin, pi / 2, pi / 2, 0.001, WRONG_AB, 0},
		{sin, 1, pi, 0.0001, GOOD, 0},
		{Const, 0, pi, 0.0001, GOOD, 6},
		{sin, 0, 2*pi, 0.0001, GOOD, -1},
		{Polynomial2, 1, 4, 0.0001, GOOD, 5},
		{Polynomial2, 4, 5, 0.0001, GOOD, 6},
	};

	n_tests = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < n_tests; i++)
	{
		x = min_step(tests[i].f, tests[i].a, tests[i].b, tests[i].eps, &err);

		printf("Tht test %d ", i + 1);

		if (err != tests[i].err)
		{
			printf("failed\n");
		}
		else if (err == WRONG_AB)
		{
			printf("has been verified\n");
		}
		else
		{
			printf("has been verified\n");
			printf("The difference between the found answer and the exact one is '%f'\n", fabs(x - tests[i].x));
		}
	}

	return 0;
}