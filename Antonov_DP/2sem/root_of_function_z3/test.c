#include <stdio.h>
#include <stdlib.h>
#include "find_root.h"

static double f1(double x);

//* функция возвращает двойное значение аргумента

double f1(double x)
{
	return 2*x;
}

typedef struct testcase{
	RRFun f;
	double a;
	double b;
	double eps;
} testcase;

int main(void)
{
	struct testcase tests[] = {
		{f1, -3, 3},
		{f2, 3,},
	};
	for (int i = 0; i < 2; i++){
		arrfun_val(tests[i].f, tests[i].arr, tests[i].len);
		for (int j = 0; j < tests[i].len; j++)
        	{
                	printf("%lf \n", tests[i].arr[j]);
        	}
	}
	return 0;
}
