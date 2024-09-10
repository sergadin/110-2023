#include <stdio.h>
#include <math.h>
#include "min_value.h"

static double f1(double x);
static double f2(double x);

// функция задаёт кубическую параболу

double f1(double x)
{
	return x * x * x;
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
	ERR exit_err;
} testcase;

int main(void)
{
	struct testcase tests[] = {
		{f1, 3, -3, 0.00001, 0, E_IO}, // здесь долджно выдать ошибку, так как a > b
		{f2, 2, 3, 0.00001, -0.25, OK}, //на вход даётся парабола [3;4]
		{f2, 1, 2 , 0.00001, 0, OK} //надо найти площадь под параболой на отрезке [1;2]
	};
	ERR err = OK;
	double answ;
	for (int i = 0; i < 3; i++){
		err = OK;
		answ = min_value(tests[i].f, tests[i].a, tests[i].b, tests[i].eps, &err);
		if ((fabs(answ - tests[i].answer) < tests[i].eps) && (tests[i].exit_err == err))
		{
			printf("test correct \n");
		}
		printf("%lf \n", answ);
	}
	return 0;
}
