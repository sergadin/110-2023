#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "approx_line.h"

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
	double a;
	double b;
	int x;
	int y;
	int len;
	double eps;
	ERR exit_err;
} testcase;

int main(void)
{
	ERR err = OK;
	double a, b;
	double x1[3] = {0, 0, 0};
	double x2[4] = {1, 2, 3, 4};
	double x3[4] = {1, 5, 3, 8};
	double y1[3] = {0, 0, 0};
        double y2[4] = {1, 2, 3, 4};
        double y3[4] = {4, 1, 8, 7};
	double **x, **y;
	x = (double **)malloc(3 * sizeof(double *));
	y = (double **)malloc(3 * sizeof(double *));
	x[0] = x1;
	x[1] = x2;
	x[2] = x3;
	y[0] = y1;
        y[1] = y2;
        y[2] = y3;
	printf("%d \n", sizeof(x2) / sizeof(double));
	struct testcase tests[] = {
                {3, -3, 1, 1, 4, 0.00001, E_LN}, // здесь долджно выдать ошибку, так как a > b
                {1, 0, 2, 2, 4, 0.00001, OK}, //на вход даётся парабола [3;4]
                {1, 2 , 3, 3, 4 ,0.00001, OK} //надо найти площадь под параболой на отрезке [1;2]
        };
	for (int i = 0; i < 3; i++){
		err = OK;
		approx_line(x3, y3, &a, &b, tests[i].len, tests[i].eps, &err);
		if ((fabs(a - tests[i].a) < tests[i].eps) && (tests[i].exit_err == err) && (fabs(b - tests[i].b) < tests[i].eps))
		{
			printf("test correct \n");
		}
		printf("%lf %lf \n", a, b);
	}
	return 0;
}
