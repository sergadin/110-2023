#include "sin.h"

typedef struct{ // create a test structure
    double x;
    double res;
    error err_code;
}dataSet;

int main(void)
{
    double result;
    double eps = 1e-6;
    error err;
    int test_num;
    dataSet tests[]={
        {M_PI/2,1.000000,OK},   //create a custom set of tests
        {1,0.841471,OK},
        {2,0.909297,OK},
        {3*M_PI,0.141123,INCORRECT_ARG},
    };

    test_num = sizeof(tests) / sizeof(tests[0]); //count the number of tests

    for (int i = 0; i < test_num; i ++) {
		result = my_sin(tests[i].x, eps, &err); //
		if(tests[i].err_code != err){
            printf("test %d failed, the expected result of the algorithm was not obtained \n",i+1);
	    }
	    else if(err == INCORRECT_ARG){
	        printf("the test %d passed, the expected error result was obtained \n",i+1);
	    }
	    else if(fabs(result-tests[i].res)>eps && err == OK){
            printf("test %d failed, %lf and %lf values ​​are different \n", i+1, result, tests[i].res);
	    }
	    else{
            printf("test %d passed, %lf and %lf values ​​are the same\n",i+1, result, tests[i].res);
	    }

    }

	return 0;
}
