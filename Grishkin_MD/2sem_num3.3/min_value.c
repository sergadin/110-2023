#include "min_value.h"

double min_value(double (*f)(double x), double a, double b,  double eps)
{
    double x1, x2, x3, f1, f2, f3, xMin, fMin;
    int lim = 1000;
    double h = (b-a)/10;
    error_code = OK;

    while (b - a > eps)
    {
        x1 = a;
        x2 = a + h;
        x3 = a + 2 * h;
        f1 = f(x1);
        f2 = f(x2);
        f3 = f(x3);
        lim--;

        while (f2 > f1 && f2 > f3)
        {
            h = h / 2;
            x2 = x1 + h;
            x3 = x1 + 2 * h;
            f2 = f(x2);
            f3 = f(x3);
        }

        if (x2 < x3)
        {
            a = x1;
            b = x3;
        }
        else
        {
            a = x2;
            b = x1;
        }
    }

    xMin = (a + b) / 2;
    fMin = f(xMin);
    if(lim < 0)
    {
        error_code = ERR;
    }
    printf("point of a minimum: %lf\n", xMin);

    return fMin;
}
