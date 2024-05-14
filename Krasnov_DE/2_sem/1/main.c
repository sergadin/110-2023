#include "fill_massiv.h"

typedef struct {
    int f_number;
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
	int test_num, funcnum_default = 4;
	int flag;
	RRFun* funcs=(RRFun[]){sine, cubing, reverseNum, naturalLog};
	error err;
	double *value_array;
	int function_num;

	/* compose a random set of tests*/

	dataSet tests[] = {
        {-1, M_PI / 2, (double[]) {1.0, 3.875785, 0.63662, 0.451583}, MALLOC_ERR},
        {funcnum_default, M_PI / 2, (double[]) {1.0, 3.875785, 0.63662, 0.451583}, OK},
		{funcnum_default, 0, (double[]) {1.0, 3.875785, 0.63662, 0.451583}, INCORRECT_ARGUMENT},
		{funcnum_default, -1, (double[]) {1.0, 3.875785, 0.63662, 0.451583}, INCORRECT_ARGUMENT},
		{2, 1, (double[]){0.841471, 1}, OK}
	};

	test_num = sizeof(tests) / sizeof(tests[0]); // counting the number of tests

	for (int i = 0; i < test_num; i++) {
        function_num = tests[i].f_number; // assign the function_num variable the value of the number of expected operations in the test

        value_array = (double*)malloc(function_num * sizeof(double));

        fillValueArray(funcs, function_num , tests[i].x, &err, value_array);

		if (err != tests[i].err_code) {
			printf(" the %d test failed, the expected result of the algorithm execution was not obtained \n", i + 1);
		}

		else if (err == INCORRECT_ARGUMENT || err == MALLOC_ERR) {
			printf(" the test %d passed, the expected error was received \n", i + 1);
		}

		else{
            flag = 1;
		    for (int j = 0; j < function_num; j++){
				if (fabs(value_array[j] - tests[i].res[j]) > eps) {
					printf("test %d failed, value at %d point is different \n", i + 1, j+1);
					flag = 0;
					break;
				}
			}
            if(flag == 1){
                printf("test %d passed successfully \n", i + 1);
            }
        free(value_array);//freeing up memory
		}
	}


	return 0;
}
