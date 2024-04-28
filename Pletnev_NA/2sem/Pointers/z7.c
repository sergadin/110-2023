#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "z7.h"

void sequence_recursive_takes(F_RR f, F_RRZ g, double x, Error *err)
{
	int limit = 10000;
	double* fn_array = (double*)(malloc((2) * sizeof(double)));
	int g1;
	double f0;
	double f1;

	fn_array[0] = (*f)(x); 
	fn_array[1] = (*f)(fn_array[0]);

	f0 = fn_array[0];
	f1 = fn_array[1];
	
	while (limit > 0)
	{
		g1 = (*g)(f0, f1);
		if (g1 == 0)
		{
			break;
		}

		fn_array[0] = fn_array[1];
		fn_array[1] = (*f)(fn_array[0]);

		f0 = fn_array[0];
		f1 = fn_array[1];

		limit--;
	}

	if (limit != 0) {
		*err = GOOD;
	}
	else {
		*err = BAD;
	}

	free(fn_array);
}