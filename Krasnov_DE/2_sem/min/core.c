#include "find_min.h"

double min_search(RRFun *f, double a, double b, double eps, error *err){
    double psi = (sqrt(5)-1)/2;
    double phi = 1 - psi;
    int limit = 1000000;
    double x;
    double d, f_d, c, f_c;
    *err = OK;
    if(a > b){
        *err = WRNG_ORD;
        return -1;
    }
    c = a + phi * (b - a);
    d = b - phi * (b - a);
    f_c = (*f)(c);
    f_d = (*f)(d);
    while(fabs(b - a)> eps && limit > 0){
        if(f_c < f_d){
            b = d;
            d = c;
            c = a + psi * (d-a);
            f_d=f_c;
            f_c=(*f)(c);
        }
        else{
            a = c;
            c = d;
            d = b - psi * (b-c);
            f_c=f_d;
            f_d=(*f)(d);
        }
        limit = limit - 1;
        if(limit==0){
            *err = LIMIT;
            return -1;
        }
    }
    x=(a+b)/2;
    return (*f)(x);
}
/*The function searches for the minimum value of the function on the back segment.
The input is a pointer to the function written in the test(RRFun *f),left and right boundaries of the segment(double a, double b),
accuracy of eps calculation and error address err.
Сalculations are carried out using the golden section method.
That is, on a given segment, points c and d are calculated according to previously known formulas,
then the values ​​​​at these points are compared and the subsequent cycle is started.
The function should return the value of the function at point x and set *err to OK if successful.
Otherwise, assign *err one of two error values ​​and return -1.*/
