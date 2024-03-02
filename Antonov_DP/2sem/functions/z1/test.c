#include <stdio.h>
#include <stdlib.h>
#include "arrfun_val.h"

double f(double x);

double f(double x)
{
	return 2*x;
}

int main(void)
{
	double *arr;
	int len = 10;
	arr = (double *)malloc(sizeof(double)*len);
	for (int i = 0; i < len; i++)
	{
		arr[i] = i;
	}
	arrfun_val(f, arr, len);
	for (int i = 0; i < len; i++)
        {
                printf("%lf \n", arr[i]);
        }
	free(arr);
	return 0;
}
