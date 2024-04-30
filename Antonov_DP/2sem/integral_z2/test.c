#include <stdio.h>
#include <math.h>
#include "integration.h"

static double f1(double x);
static double f2(double x);

// функция возвращает двойное значение аргумента

double f1(double x)
{
	return 2*x;
}

// функция, задающая параболу с корнями 2 и 3

double f2(double x)
{
	return ((x - 2) * (x - 3));
}

typedef struct testcase{
	RRFun f;
	double a;
	double b;
	double eps;
	double answer;
	int exit_err;
} testcase;

int main(void)
{
	struct testcase tests[] = {
		{f1, 3, -3, 0.00001, 0, 1}, // здесь долджно выдать ошибку, так как a > b
		{f2, 3, 4, 0.00001, 0.83333, 0}, //на вход даётся парабола [3;4]
		{f2, 1, 2 , 0.00001, 0.83333, 0} //надо найти площадь под параболой на отрезке [1;2]
	};
	int err = 0;
	double answ;
	for (int i = 0; i < 3; i++){
		err = 0;
		answ = integrate(tests[i].f, tests[i].a, tests[i].b, tests[i].eps, &err);
		if ((fabs(answ - tests[i].answer) < tests[i].eps) && (tests[i].exit_err == err))
		{
			printf("test correct \n");
		}
		printf("%lf \n", answ);
	}
	return 0;
}
