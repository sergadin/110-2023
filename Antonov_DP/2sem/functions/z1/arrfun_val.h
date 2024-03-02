#include <stdio.h>

typedef double (*RRFun)(double x);

// функция заменяет значения типа double в массиве на их значение типа
// double от функции f.
// arr - массив, в котором заменяются значения.
// len - длина массива.

void arrfun_val (RRFun f, double *arr, int len);