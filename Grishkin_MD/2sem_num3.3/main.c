#include "min_value.h"

double test_function(double x);

double test_function(double x)
{
    return x * x + 2*x - 3;
}

int main(void) {
    double a = -2, b = 2, eps = 0.001, expected = -4.0, res;

    double (*f)(double x) = test_function;

    if (a > b)
    {
        printf("wrong interval");
        return -1;
    }
    res = min_value(f, a, b , eps);

    if(error_code == ERR)
    {
        printf("limit exceeded");
        return -1;
    }

        printf("min value: %lf \n", res);

        if (fabs(res - expected) < eps)
        {
            printf("test proiden\n");
        }
        else
        {
            printf("test ne proiden, min = %lf\n", expected);
        }

    return 0;
}
