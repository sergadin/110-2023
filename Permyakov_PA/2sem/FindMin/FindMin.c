#include "FindMin.h"

double FindMin(func f, double a, double b, double eps, int* iter_c, error* err)
{
	int limit = 10000;
	double x1;
	double x2;
	double x3;
	double v1;
	double v2;
	double v3;
	(*iter_c)++;
	if (!(b > a)){
		*err = INCORRECT_ARGUMENT;
		return 0;
	}
	if (*iter_c > limit){
		*err = ITERATION_LIMIT_EXCEEDED;
		printf("%d\n", *iter_c);
		return 0;
	}
	x1 = 0.75 * a + 0.25 * b;
	x2 = 0.5 * (a + b);
	x3 = 0.25 * a + 0.75 * b;
	v1 = f(x1);
	v2 = f(x2);
	v3 = f(x3);
	if ((isnan(v1) || isinf(v1)) || (isnan(v2) || isinf(v2)) || (isnan(v3) || isinf(v3))){
		*err = INCORRECT_ARGUMENT;
		return 0;
	}
	if ((fabs(b - a) < (eps * (fabs(a + b) / 2))) || (fabs(b - a) < eps)){
                *err = OK;
                printf("найдено за %d шагов\n", *iter_c);
                return x2;
        }
	if ((v1 < v2) && (v1 < v3)){
		return FindMin(f, a, x2, eps, iter_c, err); 	
	}
	else if ((v2 < v1) && (v2 < v3)){
                return FindMin(f, x1, x3, eps, iter_c, err);                                
        }
	else if ((v3 < v1) && (v3 < v2)){
                return FindMin(f, x2, b, eps, iter_c, err);
        }
}
