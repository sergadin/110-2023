#include <stdio.h>
#include <math.h>



typedef enum{
    OK, 
    LIMIT,
    NOT_CORRECT
}Er;


double TaylorOfcos(double x, Er *error, double EPS);