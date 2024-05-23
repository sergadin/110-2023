#include <FindMin.h>

double FindMin(func f, double a, double b, double eps, int iter_c)
{
	int limit = 10000;
	double x1;
	double x2;
	double x3;
	double v1;
	double v2;
	double v3;
	iter_c++;
	if (!(b > a)){
		err = SEGMENT_ERROR;
		return 0;
	}
	x1 = 0.75 * a + 0.25 * b;
	x2 = 0.5 * (a + b);
	x3 = 0.25 * a + 0.75 * b;
	v1 = f(x1);
	v2 = f(x2);
	v3 = f(x3);
	if (isnan(res) || isinf(res)){
		err = SEGMENT_ERROR;
		return 0;
	}
	if (!(v1 > v2) & !(v1 > v3)){
		return FindMin(f, a, x1, eps, iter_c); 	
	}
	if (!(v2 > v1) & !(v2 > v3)){
                return FindMin(f, x1, x2, eps, iter_c);                                
        }
	if (!(v3 > v1) & !(v3 > v2)){
                return FindMin(f, x3, b, eps, iter_c);
        }
	if (fabs(b - a) < eps * fabs(a + b) / 2 || fabs(b - a) < eps){
		err = OK;
		fprint("найдено за %d шагов", iter_c);
		return x1;
	}
}
