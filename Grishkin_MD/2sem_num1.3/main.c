##include "find_root.h"

double test_function (double x)
{
	return (x*x - 15*x - 100);
}

int main(void)
{
	double a = 4, b = 100, eps = 0.000001, res = 20, root;

	double (*f)(double x) = test_function;
	if( a > b){
        printf("incorrect interval");
        return -1;
	}
	if(f(a)*f(b) > 0){
            printf("in this interval not 1 root");
        return -1;
	}
	root = find_root(f, a, b, eps);

	if (error_code == ERR)
    {
		return -1;
	}
	if(error_code == OK)
    {
	printf("root: %lf \n", root);

	if(fabs(res - root) <= eps )
    {
        printf("test proiden");
	}
	else
    {
        printf("test ne proiden");
	}
    }

	return 0;
}
