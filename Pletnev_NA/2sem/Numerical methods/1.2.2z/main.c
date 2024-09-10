#define _USE_MATH_DEFINES
#define pi M_PI
#define e M_E
#include "1.2.2z.h"
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

//Вспомогательная функция для тестирования: тождественная
static double Identical(double x);
//Вспомогательная функция для тестирования: квадратичная 
static double Polynomial3(double x);
//Вспомогательная функция для тестирования: константа
static double Const(double x);
//Вспомогательная функция для тестирования: экспонента
static double Exponent(double x);


static double Identical(double x)
{
	return x;
}

static double Polynomial3(double x)
{
	return (5-x)*(x+1)*(x+2) / 4 - 2;
}

static double Const(double x)
{
	return 6;
}

static double Exponent(double x)
{
	return pow(e, x);
}


int main(void)
{
	Error err;
	double x;
	int n_tests;

	BoxTest tests[] = {
		{sin, pi / 2, -pi / 2, 0.001, WRONG_AB, 0},
		{sin, pi / 2, pi / 2, 0.001, WRONG_AB, 0},
		{sin, -pi / 2, pi / 2, 0.001, GOOD, 0},
		{sin, 0, pi, 0.001, GOOD, 2},
		{Identical, 1, 5, 0.01, GOOD, 12},
		{Identical, 1, 5, 0.00001, GOOD, 12},
		{Polynomial3, -2, (2 + sqrt(43)) / 3, 0.00001, GOOD, 11.21207},
		{Exponent, 0, 2, 0.00001, GOOD, pow(e, 2) - 1},
		{Exponent, 1, 3, 0.00001, GOOD, pow(e, 3) - e}
	};

	n_tests = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < n_tests; i++)
	{
		x = trapezoid_method(tests[i].f, tests[i].a, tests[i].b, tests[i].eps, &err);

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