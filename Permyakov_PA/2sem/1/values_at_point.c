#include <values_at_point.h>


double* values_at_point(function func_array, int length, double x)
{
	double* values;
	values = (double)malloc(length*sizeof(double));
	if (values == NULL){
		return NULL;
	}
	for (int i = 0; i < length; i++){
		values[i] = func_array[i](x);
	}
	return values;
}
