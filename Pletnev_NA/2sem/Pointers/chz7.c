#include <math.h>
#define _USE_MATH_DEFINES 
#include "z7.h"
#include <stdio.h>

//Вспомогательная структура для проверки
typedef struct 
{
	F_RR f;	// функция для последовательности
	F_RRZ g;	// функция для проверки
	double x;	// действительное значение (аргумент)
	Error err;	// адрес ошибки
} BoxTest;

//Вспомогательная функция для тестирования: тождественная
static double Identical(double x);
//Вспомогательная функция для тестирования: квадратичная 
static double Polynomial2(double x);
//Вспомогательная функция для тестирования: кубическая
static double Polynomial3(double x);
//Вспомогательная функция для тестирования: показательная
static double Exponential(double x);
//Вспомогательная функция для тестирования: линейная
static double Linear(double x);

static double Identical(double x)
{
	return x;
}

static double Polynomial2(double x)
{
	return x * (x - 4);
}

static double Polynomial3(double x)
{
	return x * (5 - x) * (x + 5);
}

static double Exponential(double x)
{
	return pow(2, x);
}

static double Linear(double x)
{
	return x - 10;
}

//Вспомогательная функция для тестирования
static int COS(double x, double y);
//Вспомогательная функция для тестирования
static int SIN(double x, double y);
//Вспомогательная функция для тестирования
static int PolinomialG(double x, double y);
//Вспомогательная функция для тестирования
static int SUMM(double x, double y);
//Вспомогательная функция для тестирования
static double ExponentialY(double x, double y);


static int COS(double x, double y)
{
	int z = (int)(y * cos(x));

	return z;
}

static int SIN(double x, double y)
{
	int z = (int)(sin(x-y));

	return z;
}

static int Trigonometry(double x, double y)
{
	int z = (int)(4*cos(x) * cos(y)) + (int)(4 * sin(x) * sin(y));

	return z;
}

static int PolinomialG(double x, double y)
{
	int z = (int)(y * x + 2 * x - y + 0.5);

	return z;

}

static int SUMM(double x, double y)
{
	int z = (int)(x) + (int)(y) + 10;

	return z;
}

static double ExponentialY(double x, double y)
{
	int z = (int)(pow(x + 1, y - 2)) - 100;

	return z;
}



int main(void)
{ 
	Error err;
	double pi = M_PI;
	int n_tests;

	BoxTest tests[] = {
		{Linear, SUMM, 55, GOOD},
		{Linear, SUMM, 100000, BAD},
		{sin, COS, 0, GOOD},
		{sin, Trigonometry, pi/2, BAD},
		{Identical, SIN, pi/4, GOOD},
		{Polynomial2, PolinomialG, 4, GOOD},
		{Polynomial2, PolinomialG, 5, BAD},
		{Polynomial3, ExponentialY, 10, BAD},
		{Linear, SUMM, 106, BAD},
		{Exponential, COS, 1, BAD}
	};
	
	n_tests = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < n_tests; i++)
	{
		sequence_recursive_takes(tests[i].f, tests[i].g, tests[i].x, &err);

		if (err != tests[i].err)
		{
			printf("Tht test %d failed\n", i + 1);
		}
		else
		{
			printf("The test %d has been verified\n", i + 1);
		}
	}

	return 0;
}