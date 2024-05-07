#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "1.3root.h"


double chord_method(func f, double a, double b, double eps, error *err, int *kol_iters){
	double  fa = (*f)(a), fb = (*f)(b);
	double	fx = (*f)(a);
	int iters = 0; 
	int limit_iters = 1000000;
	double x = a;
	double c, fc;
	*err = OK; 
	
	if(a > b){
		*err = DATA_ERR;
		return -1;
	}
	if ((fa*fb) > 0){
		*err = NO_ROOT;
		return -1;
	}
	if (fabs(fa) < eps) {
		return a;
	}
	if (fabs(fb) < eps) {
		return b;
	}
	
	while((fabs(fx) > eps) && (iters < limit_iters)){
		c = a - ((fx * (b-a)) / (fb - fa)) ;
		fc = (*f)(c);
		if ((fa*fc) < 0){
			b = c;
			fb = (*f)(b);
		}
		else{
			a = c;
			fa = (*f)(a);
		}
		x = c;
		fx = fc;
		iters++;
		*kol_iters = iters;
		limit_iters--;
		if (limit_iters < 0) {
			*err = MORE_THAN_LIMIT;
			return -1;
		}
	}
	return x;
}