#include "countcos.h"
#include <math.h>

double countcos(double x, double eps, error* err) {
    const double PI = 3.1415926535;
    double cos_x = 1;
    double term = 1;
    int n = 1, limit = 10000;

    *err = OK;

    while (x > 2 * PI) {
        x = x - PI * 2;
    }

    while (x < 2 * PI) {
        x = x + PI * 2;
    }

    while (fabs(term) > eps) {
        term *= -x * x / ((2 * n - 1) * (2 * n));     // Слагаемое ряда Тейлора: 1 - x^2/2! + x^4/4! - 
        cos_x += term;
        n++;

        limit--;
        if (limit < 0) {
            *err = I_LIMIT;
            return -1;
        }
    }

    printf("Значение: %lf\n", cos_x);


    return cos_x;
}
