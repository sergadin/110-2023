#include "find_root.h"

double d2f (double(*f)(double x), double x0, double dx) // f''(x)
{
	double x11 = (f(x0+dx)-f(x0))/dx;
	double x12 = (f(x0+2*dx)-f(x0+dx))/dx;
	return (x12-x11)/dx;

}

double find_root(double (*f)(double x), double a, double b, double eps)
{
	double c=0, d=0;
	int crack = 0;
	if(fabs(f(a)) < eps){
        return a;
    }
    if(fabs(f(b)) < eps){
        return b;
    }


	// smotrim na znak proizvedeniya f''(x) i f(x), chtobi ponyat' otkuda schitat'
	if (d2f(f, a, eps)*f(a)>0)
	{
		c=a;
		d=b;
		crack += 1;
	}
	if (d2f(f, b, eps)*f(b)>0)
	{
		c=b;
		d=a;
		crack += 1;
	}
	if (crack==1){
	    double x1=c,x2=c;
	    int iter = 0;
	    while (fabs(d-x2)>eps)
	    {
		    iter++;
            x1 = d-f(d)*(c-d)/(f(c)-f(d));
	        x2=d;
            d=x1;
        }
        printf("number of iterations: %d\n",iter);
	    }
        else
	    {
            printf("Method can't be used");// f''(x) ne soxranyaet znak
            return a - 1;
        }
	return d;
}
