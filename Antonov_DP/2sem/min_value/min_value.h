#include <stdio.h>
#include <math.h>

typedef double (*RRFun)(double x);

typedef enum { OK = 0, E_IO } ERR;

// функция находит минимум функции f на отрезке [a;b] методом параболы, с помощью разбиения равномерной сетки
// a - начало отрека и b - конец отрека a < b
// eps - точность минимума
// все данные типа double

double min_value (RRFun f, double a, double b, double eps, ERR *err);
