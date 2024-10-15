#include "min_value.h"

double test_function(double x);

double test_function(double x)
{
	return (sin(x));
}
int main(void)
{
	double a = 0, b = 3, eps = 0.0001, expected = 0.00;
	double (*f)(double x) = test_function;

	double res = min_value(f, a, b, eps);

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
