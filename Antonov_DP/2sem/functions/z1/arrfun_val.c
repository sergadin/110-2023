#include <stdio.h>
#include <stdlib.h>
#include "arrfun_val.h"

void arrfun_val (RRFun f, double *arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		arr[i] = f(arr[i]);
	}
}
