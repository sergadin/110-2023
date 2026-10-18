#include "taylor_sin.h"

double taylor_sin(double x, double eps, Error* err) {
    double sin_x = 0;
    double term = x;
    int n = 1, limit = 1000;

    *err = OK;

    if (!(x > -2 * 3.141592 && x < 2 * 3.141592)) {
        *err = W_ARG;
        return -1;
    }

    while (fabs(term) > eps) {
        sin_x += term;
        term = -term * x * x / ((2 * n) * (2 * n + 1));     // Слагаемое ряда Тейлора: x - x^3/3! + x^3/5 - ...
        n++;

        limit--;
        if (limit < 0) {
            *err = LIMIT_0;
            return -1;
        }
    }

    printf("Значение: %lf\n", sin_x);


    return sin_x;
}