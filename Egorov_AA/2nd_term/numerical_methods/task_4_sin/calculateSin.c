#include "calculateSin.h"

double calculateSin(double x, double eps, error* err) {
    double sin_x = 0;
    double term = x;
    int n = 1, limit = 10000;

    *err = OK;

    if (!(x > -2 * M_PI && x < 2 * M_PI)) {
        *err = INVALID_ARGUMENT;
        return -1;
    }

    while (fabs(term) > eps) {
        sin_x += term;
        term = -term * x * x / ((2 * n) * (2 * n + 1));     // Слагаемое ряда Тейлора: x - x^3/3! + x^3/5 - ...
        n++;

        limit--;
        if (limit < 0) {
            *err = I_LIMIT_EXCEEDED;
            return -1;
        }
    }

    printf("Значение: %lf\n", sin_x);


    return sin_x;
}
