#include "min_value.h"

double min_value(double (*f)(double x), double a, double b, double eps)
{
	double c, c0, c1, c2, point, buf;
	if (a > b)
    {
        buf = a;
	    a = b;
	    b = buf;
    }

	while (fabs(b-a)>eps)
    {
			c = (a + b)/2;
			c2 = ((f(c)-f(a))/(c-a) - (f(b)-f(a))/(b-a))/(c-b);
			if (c2 == 0)
			{
				if(f(a)<f(b))
				{
                    b = (a+c)/2;
                }
				else {a = (c+b)/2;}
			}
			else
            {
                c1 = (f(c)-f(a))/(c-a) - c2*(c+a);
			    c0 = f(a)-a*c1 - a*a*c2;
			    point = -c1/2/c2;
			    if (c2 > 0)
			    {
			        if (point > c)
			        {
			            a = c;
                    }
			        else
			        {
			            b = c;
                    }
                }
			    if(c2 < 0)
                {
                    if (point < c)
			        {
			            a = c;
                    }
			        else
			        {
			            b = c;
                    }
                }
            }
    }
	return c;

}









