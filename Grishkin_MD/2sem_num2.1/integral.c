#include "integral.h"

double integral(double (*f)(double x), double a, double b, double eps)
{
    double ans = 0, last_ans = 1, dx, n = 1;
	double x=a;
	int limit = 100;

	while (fabs(last_ans - ans) > eps)
	{
		last_ans = ans;
		ans = 0;
		n = n*2;
		dx = (b-a)/n;
		limit --;
		while (x<=b)
			{
				ans+=f(x)*dx;
				x+=dx;
			}
			x = a;
	}
	//printf("%d \n", limit);

	if (limit < 0){
       printf("func cant be integrated");
       error_code = ERR;
	}
	//printf("%lf\n", ans);
	return ans;
}









