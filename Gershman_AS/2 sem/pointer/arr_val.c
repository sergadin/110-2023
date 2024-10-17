#include "arr_val.h"

double* arr_of_val(RRFun* func, int len, double x, Error* err) {
    double* res;
    res = (double*)malloc(len * sizeof(double));
    if (res == NULL) {
        *err = MEM_ER;
        return 0;
    }
    for (int i = 0; i < len; i++) {
        double res_i;
        res_i = func[i](x);
        res[i] = res_i;
    }
    *err = OK;
    return res;
}



