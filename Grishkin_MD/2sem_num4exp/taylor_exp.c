#include "taylor_exp.h"

double factorial(double x)
{
	double n = 1, ans = 1;
	while (n<=x)
	{
		ans = ans * n;
		n++;
	}
	return ans;
}

double taylor_exp(double x, double eps)
{
   double ans = 1, last_ans = 0, n = 1;
   int limit = 10000;
	
	while (fabs(last_ans - ans) > eps)
	{
		last_ans = ans;
		limit--;

		ans += (pow(x,n)/factorial(n));
		n++;
	}
	if(limit < 0)
        {
            error_code = LIM;
	}
	error_code = OK;

    //printf("%lf \n", n);
    return ans;
}
