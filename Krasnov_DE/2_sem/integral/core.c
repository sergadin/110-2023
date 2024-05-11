#include "integral.h"

double Gauss_caunting(RRFun *f, double a, double b){
    double integral = 0.5 * (b - a) *
		((*f)(0.5 * (a + b - ((b - a) / sqrt(3)))) + (*f)(0.5 * (a + b + ((b - a) / sqrt(3)))));
    return integral;
}//the function calculates the Gaussian quadrature on a given segment

double Integral_count(RRFun *f, double a, double b, double eps, error *err){
    *err = OK;
    int limit = 10000;
    double new_integral = 0, old_integral = 0;
    int n = 2, i;
    double dx = (b - a) / n;

    if(a >= b){
        *err = WRNG_ORD;
        return -1;
    }

    for(i = 0; i < n; i++){
        old_integral = old_integral + Gauss_caunting(f, a + dx * i, a + dx * (i+1));
    }

    n = n * 2;
    dx = dx / 2;

    for(i = 0; i < n; i++){
        new_integral = new_integral + Gauss_caunting(f, a + dx * i, a + dx * (i+1));
    }

    limit = limit - 1;

    while(fabs(new_integral - old_integral) > eps && limit > 0){
        old_integral = new_integral;
        new_integral = 0;
        n = n * 2;
        dx = dx / 2;
        for(i=0; i < n; i++){
            new_integral = new_integral + Gauss_caunting(f, a + dx * i, a + dx * (i+1));
        }
        limit = limit - 1;
    }

    if(limit == 0){
        *err = LIMIT;
        return -1;
    }

    return new_integral;
}
/*The function receives as input the function address (RRFun *f),
 the left and right boundaries of the segment (double a double b), the calculation accuracy (eps), and the error address (*err).
 The function calculates the integral of the function using Gaussian quadrature, if the program executes successfully,
  it will return the value of the integral and assign *err the value OK.*/

