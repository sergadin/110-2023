#include "./utils/utils.h"

double Composition_of_function(double x, int n, Fun *Functions)
{
    double y = x;
    for(int i = n-1; i >= 0; i--)
     y = Functions[i](y);
     return y;
}//Функция, которая принимает на вход зачение x, от которого нужно найти композицию, n- количество функций в композиции,
//массив указателей на функкции из R в R, выдает значение композиций этих функций в этой точке.