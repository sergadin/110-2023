#include "fill_massiv.h"
double* fillValueArray(RRFun* functions, int func_num, double x, error* err,double *value_array) {
        double res;
        int i;
        *err=OK;
	for (i = 0; i < func_num; i++) {
		res = functions[i](x);
		if (isnan(res) || isinf(res)) {
			*err = INCORRECT_ARGUMENT;
		}
		value_array[i] = res;
	}
	return value_array;
}

/*
    Function fillValueArray fills an array with function values ​​at a given point.
    The function receives as input the address of the array of functions (RRFun* functions),
    the number of functions in this array (int func_num), the variable x(double x),
    the address of the error (error* err), and the address of the array of values ​​(double *value_array).
    If successful, the function sets *err to OK and returns the address of the array of function values ​​at the given point.
*/
