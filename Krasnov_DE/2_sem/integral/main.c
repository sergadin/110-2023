#include "integral.h"

typedef struct {    //creating a test structure
    RRFun f;
	double a;
	double b;
	double res;
	error err_code;
} dataSet;

static double func1(double x);  //function declarations
static double func2(double x);
static double func3(double x);
static double func4(double x);
static double func5(double x);
static double func6(double x);

static double func1(double x){  //description of functions
	return ((x * x)+2);
}

static double func2(double x){
	return (x + 3);
}

static double func3(double x){
	x = 2;
	return x;
}

static double func4(double x){
	return pow(x, 4) + 55 * x - 17;
}

static double func5(double x){
	return pow(x, 5);
}

static double func6(double x){
	return pow(10, x);
}

static double func7(double x){
	return sin(1/x);
}


int main(void)
{
    error err;
    double result;
    double eps = 1e-6;
    int test_num;
    int i;
    dataSet tests[] = { //creating a test suite
    {func1, 1, 3, 12.666667, OK},
	{func2, 5, 162, 13580.5, OK},
	{func3, -4, -0.5, 7, OK},
	{func4, 4, 1, -1, WRNG_ORD},
	{func5, -5, 5, 0, OK},
	{func6, 2, 5, 43386.017380, OK},
	{func7, 0, 2, 10, LIMIT}
	};

	test_num = sizeof(tests) / sizeof(tests[0]); //count the number of tests

	for (i = 0; i < test_num; i++){
	    result = Integral_count(&tests[i].f, tests[i].a, tests[i].b, eps, &err);

	    if(tests[i].err_code != err){
            printf("the test %d failed, the expected result of the algorithm execution was not obtained\n",i+1);
	    }
	    else if (err == WRNG_ORD || err == LIMIT) {
			printf("test %d passed, the expected error was received\n", i + 1);
		}
		else if((err == OK) && ((fabs(result-tests[i].res)) > eps)){
			printf("test %d failed, %lf and %lf values ​​do not match\n", i +1, tests[i].res, result);
		}
		else if((err == OK) && ((fabs(result-tests[i].res)) < eps)){
			printf("test %d passed successfully, %lf and %lf values ​​are the same\n", i +1, tests[i].res, result);
		}
	}

    return 0;
}

