#include "taylor_exp.h"

int main(void)
{
    double eps = 0.0001, x = 5, expected = 148.413159103, res;
	
    res = taylor_exp(x, eps);

    if(error_code == LIM)
    {
        printf("the iteration limit has been exceeded\n");
        return -1;
    }
    if(error_code == OK)
    {
	    printf("%lf\n", res);
	    if(fabs(res - expected) < eps)
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
