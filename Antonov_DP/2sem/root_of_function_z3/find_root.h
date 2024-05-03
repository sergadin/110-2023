#include <stdio.h>
#include <math.h>

typedef double (*RRFun)(double x);

typedef enum { OK = 0, E_NL, E_SS } ERR; /* E_NL - начало отрезка больше конца, E_SS - значения функции на концах одного знака */

// функция находит один корень заданной функции f , переводящей из double в double, на отреке [a;b] методом хорд с точность eps
// a - начало отрека и b - конец отрека a<b
// eps - точность корня
// все данные типа double

double find_root (RRFun f, double a, double b, double eps, ERR *err);
