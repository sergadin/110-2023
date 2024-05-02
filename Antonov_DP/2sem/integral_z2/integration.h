#include <stdio.h>
#include <math.h>

typedef double (*RRFun)(double x);

typedef enum { OK = 0, E_IO } ERR;

// функция находит интеграл f на отрезке [a;b] методом трапеций
// a - начало отрека и b - конец отрека a < b
// eps - точность интеграла
// все данные типа double

double integrate (RRFun f, double a, double b, double eps, ERR *err);
