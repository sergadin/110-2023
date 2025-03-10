#include "Array_of_values.h"

double* arrayOfValues(RRFun* func, int len, double x, error* err) {
    double* arr;
    arr = (double*)malloc(len*sizeof(double));
    if (arr == NULL) {
		printf("memory error\n");
		*err = MEMORY;
		return 0;
	}
	for (int i = 0; i < len; i++){
        double res;
		res = func[i](x);
		//printf("%lf\n", res);
        if (isnan(res) || isinf(res)) {
            printf("incorrect arg\n");
            *err = PARAM;
            free(arr);
            return 0;
        }
        arr[i] = res;
	}
	*err = OK;
	return arr;
}




