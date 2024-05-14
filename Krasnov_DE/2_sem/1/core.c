#include "fill_massiv.h"
double fillValueArray(RRFun* functions, int func_num, double x, error* err,double *value_array) {
    if (value_array==NULL){
        *err=MALLOC_ERR;
        return -1;
    }
    if(func_num>  4){
        *err = INCORRECT_ARGUMENT;
        return -1;
    }

    printf("func_num=%d\n",func_num);
	for (int i = 0; i < func_num; i++) {
		double res;
		res = functions[i](x);
		if (isnan(res) || isinf(res)) {
			*err = INCORRECT_ARGUMENT;
			return -1;
		}
		value_array[i] = res;
	}
	*err = OK;
	return 0;
}

/*
    The fillValueArray function receives as input a pointer to an array of functions (RRFun* functions),
    ,number of functions expected in the test, variable x, which will be substituted in the function,
    pointer to error, pointer to array of function values ​​at point.
    The function alternately checks the convergence of the results and the values ​​specified in the tests.
    The function also returns an error pointer (INCORRECT_ARGUMENT,MALLOC_ERR) or the value OK.
    If the comparison is successful, the function will output 0 and assign the value OK*/
