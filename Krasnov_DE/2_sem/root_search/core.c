#include "root_search.h"

double root_search(RRFun *f, double a, double b, double eps, error *err){
	double x, f_x, f_a = (*f)(a), f_b = (*f)(b);
	int limit = 100000;
	*err = OK;
	if(a > b){
        *err = WRNG_ORD;
        return -1;
	}
	if(f_a == f_b){
        *err = EQUAL_VAL;
        return -1;
	}
	if (f_a * f_b > 0){
        *err = NO_ROOT;
        return -1;
    }
    x = (a * f_b - b * f_a) / (f_b - f_a);
    f_x = (*f)(x);
    if(fabs(f_a) < eps){
        *err = OK;
        printf("1 operation\n");
        return a;
    }
    else if(fabs(f_b) < eps){
        *err = OK;
        printf("1 operation\n");
        return b;

    }
    else if(fabs(f_x) < eps){
        *err = OK;
        printf("1 operation\n");
        return x;
    }
    while((fabs(f_x) > eps) && (limit>0)){
        if ((f_x*f_a) >= 0){
            a = x;
            f_a = f_x;
        }
        else if ((f_x * f_b)>=0){
            b = x;
            f_b = f_x;
        }
        else{
            *err = NO_ROOT;
            return -1;
        }
         if(fabs(f_b - f_a) < eps){
            *err = EQUAL_VAL;
            return -1;
        }
        x = (a * f_b - b * f_a)/(f_b - f_a);
        f_x = (*f)(x);
        limit = limit-1;

    }

    if (limit == 0){
    	*err = NO_ROOT;
    	return -1;
    }
    printf("number of operations=%d\n",100000-limit);


    return x;

}
/*The function will take as input a pointer to the function in the test, the left boundary of the segment,
the right boundary of the segment, the accuracy of calculations, and a pointer to the error.
First of all, the presence of roots at the ends of the segment and point c, obtained using the formula of the chord method, is checked.
If there are none, a cycle is launched that works using the chord method.
*/


