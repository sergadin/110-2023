#define _USE_MATH_DEFINES 
#include "1.1.2z.h"
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
static double Polynomial2(double x);
//Вспомогательная функция для тестирования: кубическая
static double Polynomial3(double x);
//Вспомогательная функция для тестирования: константа
static double Const(double x);
//Вспомогательная функция для тестирования: константа
static double Const(double x);

static double Identical(double x)
{
	return x;
}

static double Polynomial2(double x)
{
	return x * x;
}

static double Polynomial3(double x)
{
	return x * (5 - x) * (x + 5);
}

static double Const(double x)
{
	return 6;
}

int main(void)
{
	Error err;
	int c;
	double x;
	double pi = M_PI;
	int n_tests;

	BoxTest tests[] = {
		{sin, pi / 2, -pi / 2, 0.001, WRONG_AB, 0},
		{sin, pi / 4, pi / 4, 0.001, WRONG_AB, 0},
		{sin, -pi / 2, pi / 2, 0.001, WRONG_f, 0},
		{sin, -pi / 4, pi / 4, 0.001, GOOD, 0},
		{cos, 0, 7 * pi / 4, 0.0001, GOOD, 3 * pi / 2},
		{Polynomial2, -2, 2, 0.00001, GOOD, 0},
		{Polynomial3, 3, 6, 0.00001, GOOD, 5},
		{Polynomial3, 2, 4, 0.00001, LIMIT_0, 5},
		{Const, 3, 6, 0.00001, WRONG_f, 5},
		{Identical, -1, 4, 0.00001, GOOD, 0},
		{Identical, -1, 100000, 0.00001, GOOD, 0},
	};

	n_tests = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < n_tests; i++)
	{
		x = newton_tangent_method(tests[i].f, tests[i].a, tests[i].b, tests[i].eps, &err, &c);

		if (err != tests[i].err)
		{
			printf("Tht test %d failed\n", i + 1);
		}
		else if (err == GOOD)
		{
			printf("The test %d has been verified. Iterations done '%d'. The difference between the found answer and the exact one is '%f'\n" , i + 1, c, fabs(x- tests[i].x));
		}
		else
		{
			printf("The test %d has been verified\n", i + 1);
		}
	}

	return 0;
}