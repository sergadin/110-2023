#include "fill_massiv.h"

typedef struct {
	double x;
	double* res;
	error err_code;
} dataSet;          //creating a test structure


double sine(double x);
double cubing(double x);
double reverseNum(double x);
double naturalLog(double x);

double sine(double x) {
	return sin(x);
}

double cubing(double x) {
	return x * x * x;
}

double reverseNum(double x) {
	return 1 / x;
}

double naturalLog(double x) {
	return log(x);
}

int main(void) {
	const double eps = 1e-6;
	int test_num, i, j, function_num = 4;
	double *value_array;
	int flag;
	RRFun* funcs=(RRFun[]){sine, cubing, reverseNum, naturalLog};
	error err;

	/* compose a random set of tests*/

	dataSet tests[] = {
        {M_PI , (double[]) {0, 31.006276, 0.31831, 1.14473}, OK},
        {M_PI / 2, (double[]) {1.0, 3.875785, 0.63662, 0.451583}, OK},
		{0, (double[]) {1.0, 3.875785, 0.63662, 0.451583}, INCORRECT_ARGUMENT},
		{-1, (double[]) {1.0, 3.875785, 0.63662, 0.451583}, INCORRECT_ARGUMENT},
	};

	test_num = sizeof(tests) / sizeof(tests[0]); // counting the number of tests

    value_array = (double*)malloc(function_num * sizeof(double));

	for (i = 0; i < test_num; i++) {

        value_array = fillValueArray(funcs, function_num , tests[i].x, &err, value_array);

		if (err != tests[i].err_code) {
			printf(" the %d test failed, the expected result of the algorithm execution was not obtained \n", i + 1);
		}

		else if (err == INCORRECT_ARGUMENT ) {
			printf(" the test %d passed, the expected error was received \n", i + 1);
		}

		else{
            flag = 1;
		    for (j = 0; j < function_num; j++){
				if (fabs(value_array[j] - tests[i].res[j]) > eps) {
					printf("test %d failed, value at %d point is different \n", i + 1, j+1);
					flag = 0;
					break;
				}
			}
            if(flag == 1){
                printf("test %d passed successfully \n", i + 1);
            }

		}

	}
	free(value_array);


	return 0;
}
