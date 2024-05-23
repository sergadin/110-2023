#include "determine_values.h"


double* determine_values(func f, double* X, double* Y, int n, error* err)
{
	double* values_arr;
	double xi;
	double yi;
	double res;
	values_arr = (double*)malloc(n * sizeof(double));
	if (!(values_arr)){
		printf("проблема с выделением памяти\n");
		*err = MALLOC_ERROR;
		return 0;
	}
	for (int i = 0; i < n; i++){
		res = f(xi, yi);
		if (isnan(res) || isinf(res)){ 		// проверка на попадение в область определения
							// из библиотеки
                        printf("неверный аргумент\n");
                        *err = INCORRECT_ARGUMENT;
                        free(values_arr);
                        return 0;
                }
                values_arr[i] = res;
	}
	*err = OK;
	return values_arr;
}
