#include <stdio.h>
#include <math.h>

typedef double (*RRFun)(double x);

// функция находит один корень заданной функции f , переводящей из double в double, на отреке [a;b] методом хорд с точность eps
// a - начало отрека и b - конец отрека a<b
// eps - точность корня
// все данные типа double

double find_root (RRFun f, double a, double b, double eps, int *err);
