#include "sin.h"


typedef struct{     //create the test structure
    double x;
    double eps;
    double res;
}dataSet;

int main(void)
{
    double result;
    const double pi = 3.1415926535, eps = 1e-6;
    int test_num;
    dataSet tests[]={   //create various tests
        {pi/2,eps,1.000000},
        {1,eps,0.841471},
        {2,eps,0.909297},
        {3,eps,0.141123},
    };

    test_num = sizeof(tests) / sizeof(tests[0]);    //count the number of tests

    for (int i = 0; i < test_num; i ++) {   //we start the loop with functions that calculate the sine of a given angle
		result = my_sin(tests[i].x, tests[i].eps);
		if (fabs(result - tests[i].res) < eps) {
			printf("test %d passed successfully, sin(%lf) = %lf\n", i + 1, tests[i].x, result);
		}
		else {
			printf("test %d failed, the value of the resulting function %lf differs from the value in the test %lf\n", i + 1, result,tests[i].res);
		}
	}

	return 0;
}
