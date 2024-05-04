#include <math.h>
#include <stdio.h>
#include "find_min.h"
#define LIMIT 10000


double find_min(Rfun f, double a, double b, double eps, Error* error);
double get_min(Rfun f, double a, double b, double eps, Error* error);


double get_min(Rfun f, double a, double b, double eps, Error* error){
    double x1, x2;
    double f1, f2;

    x1 = (a + b) / 2;
    x2 = (x1 + b) / 2;
    f1 = (*f)(x1);
    f2 = (*f)(x2);

    for (int i = 0; i < LIMIT; i++) {
        if (f1 < f2) {
            b = x2;
            x2 = x1;
            x1 = (a + b) / 2;
            f2 = f1;
            f1 = (*f)(x1);
        } else {
            a = x1;
            x1 = x2;
            x2 = (x2 + b) / 2;
            f1 = f2;
            f2 = (*f)(x2);
        }
        if (x2 - x1 < eps) {
            if (f1 < f2) {
                *error = OK;
                return f1;
            } else {
                *error = OK;
                return f2;

            }
        }
    }
    *error = OP_LIMIT;

}



double find_min(Rfun f, double a, double b, double eps, Error* error) {
    double min;
    min = get_min(f, a, b, eps, error);
    return min;
}





