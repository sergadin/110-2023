#include <math.h>
#include <stdio.h>
#include "find_min.h"
#define LIMIT 10000

double find_min(Rfun f, double a, double b, double eps, Error *error);
static int get_coef(Rfun f, double a, double b, double eps, double *t1, double *t2, double *t3);
double min_of_par(double x1, double x2, double x3, double y1, double y2, double y3);

// Функция возвращает минимум параболы, построенное по 3 заданным точкам
double min_of_par(double x1, double x2, double x3, double y1, double y2, double y3)
{
    double a, b, c;
    double min_x;
    double min_val;
    a = (y3 - (x3 * (y2 - y1) + x2 * y1 - x1 * y2) / (x2 - x1)) / (x3 * (x3 - x1 - x2) + x1 * x2);
    b = (y2 - y1) / (x2 - x1) - a * (x1 + x2);
    c = (x2 * y1 - x1 * y2) / (x2 - x1) + a * x1 * x2;
    min_x = -b / (2 * a);
    min_val = a * min_x * min_x + b * min_x + c;
    return min_val;
}

// Функция делением отрезка находит точку минимума
static int get_coef(Rfun f, double a, double b, double eps, double *t1, double *t2, double *t3)
{
    double x1, x2;
    double f1, f2;

    x1 = a + ((b - a) / 2);
    x2 = x1 + ((b - x1) / 2);
    f1 = (*f)(x1);
    f2 = (*f)(x2);

    for (int i = 0; i < LIMIT; i++)
    {
        if (f1 < f2)
        {
            b = x2;
            x2 = x1;
            x1 = a + ((x2 - a) / 2);
            f2 = f1;
            f1 = (*f)(x1);
        }
        else
        {
            a = x1;
            x1 = x2;
            x2 = x2 + ((b - x2) / 2);
            f1 = f2;
            f2 = (*f)(x2);
        }
        if (x2 - x1 < eps)
        {
            if (x2 == x1)
            {
            }
            if (f1 < f2)
            {
                *t1 = a;
                *t2 = x1;
                *t3 = x2;
                return 1;
            }
            else
            {
                *t1 = a;
                *t2 = x2;
                *t3 = b;
                return 1;
            }
        }
    }
    return -1;
}

double find_min(Rfun f, double a, double b, double eps, Error *error)
{
    double x1, x2, x3;
    double min;
    if (get_coef(f, a, b, eps, &x1, &x2, &x3))
    {
        *error = OK;
    }
    else
    {
        *error = OP_LIMIT;
    }
    min = min_of_par(x1, x2, x3, (*f)(x1), (*f)(x1), (*f)(x2));
    return min;
}
