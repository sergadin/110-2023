#include <stdio.h>
#include <math.h>
#define EPS 0.00001
#define PI 3.14159265358



typedef double (*RFun)(double);


typedef enum{
    OK,
    LIMIT,
    HAVE_NO_ROOT,
    NOT_CORRECT // метод не применим
}Er;

double FindingTheRoot(RFun f, RFun g, double a, double b, int *count, Er *error); // f - функция, g - производная функции f
