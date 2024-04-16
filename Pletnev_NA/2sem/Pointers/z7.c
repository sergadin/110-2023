#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "z7.h"

double sequence_recursive_takes(F_RR f, F_RR g, double x, double eps, Error *err)
{
	int limit = 10000;
	int i = 0;
	double* fn_array = (double*)(malloc((limit + 1) * sizeof(double)));
	fn_array[i] = (*f)(x);

	while (limit > 0)
	{
		i++;
		fn_array[i] = (*f)(fn_array[i-1]);
		if ((fabs((*g)(fn_array[i-1])) < eps) && (fabs((*g)(fn_array[i])) < eps))
		{
			break;
		}
		limit--;
	}

	if (limit != 0) {
		*err = GOOD;
	}
	else {
		*err = BAD;
	}
}