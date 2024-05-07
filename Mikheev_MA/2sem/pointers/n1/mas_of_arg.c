#include "mas_of_arg.h"

void mas_of_arg(RRFun f, double x, double *mas_arg, Er *error, int i){
    mas_arg[i] = f(x);
    if(isnan(mas_arg[i]) || isinf(mas_arg[i])){       // если значение стремится в бесконечность или неопределено
        printf("Некорректный аргумент для данной функции в тесте №%d\n", i + 1);
        *error = NOT_OK;
    }
}
