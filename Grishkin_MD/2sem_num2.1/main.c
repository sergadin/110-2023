#include "integral.h"

double test_function (double x)
{
	return (x*x - x - 5);
}

int main(void)
{
	double a = 10, b = 14, eps = 0.0001, expected = 513.3333;
	double (*f)(double x) = test_function;

	double res = integral(f, a, b, eps);

	if(a>b){
        printf("wrong interval");
        return -1;
	}

	if(error_code == ERR){
        return -1;
	}
	if(error_code == OK){
        printf("%lf\n", res);
        if(fabs(res - expected) < eps) {
            printf("test proiden\n");
        }
        else{
            printf("test ne proiden\n");
        }
	}
	return 0;
}
