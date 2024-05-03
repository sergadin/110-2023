#include <stdio.h>
#include <stdlib.h>
#include "arrfun_val.h"

static double f(double x);

//* функция возвращает двойное значение аргумента
double f(double x)
{
	return 2*x;
}

typedef struct testcase{
	RRFun f;
	int len;
	double *arr;
} testcase;

int main(void)
{
	double arr[]={1, 2, 3};
	struct testcase tests[] = {
		{f, 3, arr},
		{f, 3, arr},
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
