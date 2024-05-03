#include <stdio.h>
#include <stdlib.h>

typedef double (*RRFun)(double x);
typedef enum { OK = 0, E_DATA, E_IO } ERR;

void arfun_val(RRFun f, double *arr, int len, ERR err);

void arfun_val(RRFun f, double *arr, int len, ERR err)
{
	for (i = 0; i < len; i++)
	{
		arr[0] = f(arr[0]);
	}
}
