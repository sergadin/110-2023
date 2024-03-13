#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "simpson_integral.h"


double simpson_integral(int n, double a, double b, Rfun f, Error *error) {
    const double width = (b-a)/n;

    double simpson_integral = 0;
    for(int step = 0; step < n; step++) {
        const double x1 = a + step*width;
        const double x2 = a + (step+1)*width;

        simpson_integral += (x2-x1)/6.0*((*f)(x1) + 4.0*(*f)(0.5*(x1+x2)) + (*f)(x2));
    };
    
    if (!(isnan(simpson_integral)) && !(isinf(simpson_integral))) {
    	*error = OK;
    } else {
    	*error = NOT_A_NUMBER;
    }
	
    return simpson_integral;
}
