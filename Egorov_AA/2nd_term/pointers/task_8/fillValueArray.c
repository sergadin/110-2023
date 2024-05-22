#include "fillValueArray.h"


double* fillValueArray(RRFun* functions, int func_num, double x, error* err) {
	double* value_array;
	value_array = (double*)malloc(func_num*sizeof(double));
	if (value_array == NULL) {
		printf("Память не выделена\n");
		*err = MALLOC_ERR;
		return 0;
	}
	for (int i = 0; i < func_num; i++) {
		double res;
		res = functions[i](x);
		if (isnan(res) || isinf(res)) {                // функции из библиотеки math.h. Если значение неопределено(NaN) 
			printf("Неверный аргумент\n");         // или стремится к бесконечности(inf), функция выдаст ошибку.
			*err = INCORRECT_ARGUMENT;
			free(value_array);
			return 0;
		}
		value_array[i] = res;
	}
	*err = OK;
	return value_array;
}
