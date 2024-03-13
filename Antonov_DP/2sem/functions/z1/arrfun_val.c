#include <stdio.h>
#include <stdlib.h>
#include "arrfun_val.h"

//* Действие функции объясняется в заголовочном файле.

void arrfun_val (RRFun f, double *arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		arr[i] = f(arr[i]);
	}
}
