#include "fillValueArray.h"


double* fillValueArray(RRFun* functions, int func_num, double x, error* err) {
	double* value_array;
	value_array = (double*)malloc(func_num*sizeof(double));
	if (value_array == NULL) {
		*err = MALLOC_ERR;
		return -1;
	}
	for (int i = 0; i < func_num; i++) {
		double res;
		res = functions[i](x);
		if (isnan(res) || isinf(res)) {
			*err = INCORRECT_ARGUMENT;
			return -1;
		}
		value_array[i] = res;
		printf("%lf\n", value_array[i]);
	}
	*err = OK;
	return value_array;
}