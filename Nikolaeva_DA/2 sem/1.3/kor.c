#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "kor.h"

double chord_metod(RRFun f, double a, double b, double eps, int *max_iter, Error *err){
	double  f_a = (*f)(a), f_b = (*f)(b), f_x = (*f)(a);
	int iter = 0, limit = 10000;
	double x = a;
	double c;
	double f_c;

	if (a > b){
		*err = NO_ITER;
		return -1;
		*err = OK;
	}
	if (f_a * f_b > 0){
		*err = NO_FUNC;
		return -1;
	}
	if (fabs(f_a) < eps) {
		printf("Корень - %lf\n", c);
		return a;
	}

	if (fabs(f_b) < eps) {
		printf("Корень - %lf\n", c);
		return b;
	}

	while(fabs(f_x) > eps && iter < limit){
			c = a - f_x * (b-a) / ((*f)(b) - (*f)(a)) ;
		        f_c = (*f)(c);
			if (f_a * f_c < 0){
			b = c;
			}
			else{
				a = c;
			}
			x = c;
			f_x = f_c;
			iter++;
	}
	limit--;
		if (limit < 0) {
			*err =LIMIT_NO;
			*max_iter = iter;
			return -1;
		}
		if (limit == 0){
	    	*err = NA_NO_ROOT;
	    	*max_iter = iter;
	    	return -1;
	    	
    	}
        printf("Корень - %lf\n", x);
    *max_iter = iter;
	return x;
}





