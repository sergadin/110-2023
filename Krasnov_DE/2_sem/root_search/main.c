#include "root_search.h"
//creating a test structure//
typedef struct {
    RRFun f;
	double a;
	double b;
	double res;
	error err_code;
} dataSet;

//creating a feature set//
static double parabola(double x);
static double straight_line(double x);
static double constanta(double x);
static double power_func(double x);

static double parabola(double x){
	return ((x*x)-2);
}

static double straight_line(double x){
	return (x-10);
}

static double constanta(double x){
	return 2;
}
static double power_func(double x){
	return pow(x,4)+55*x-17;
}



int main(void)
{
    error err;
    double result;
    double eps=1e-6;
    int test_num;
    //creating a test suite//
    dataSet tests[] = {
    {parabola, 0.5, 3, 1.414213, OK},
	{straight_line, -5, 20, 10, OK},
	{constanta, -4, -0.5, -1, EQUAL_VAL},
	{power_func, 4, 1, -1, WRNG_ORD}
	};
    //count the number of tests//
	test_num = sizeof(tests) / sizeof(tests[0]); //count the number of tests

	for (int i = 0; i < test_num; i++){
	    result=root_search(&tests[i].f,tests[i].a,tests[i].b,eps,&err);
	    if(tests[i].err_code!=err){
            printf("the test %d failed, the expected result of the algorithm execution was not obtained \n",i+1);
	    }
	    else if (err == WRNG_ORD || err == EQUAL_VAL || err== NO_ROOT) {
			printf("the test %d passed, the expected error was received\n", i + 1);
		}
		else if((err == OK) && ((fabs(result-tests[i].res)) >= eps)){
			printf("test %d failed, root values ​​%lf and %lf do not match\n", i +1, tests[i].res, result  );
		}
		else if((err == OK) && ((fabs(result-tests[i].res)) < eps)){
			printf("the test %d passed successfully, the values ​​of the roots %lf and %lf coincide\n", i +1, tests[i].res, result  );
		}
	}

	return 0;

}
