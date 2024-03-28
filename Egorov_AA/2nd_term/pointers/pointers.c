#include "fillValueArray.h" 
	
double sine(double x);
double cubing(double x);
double reverseNum(double x);
double naturalLog(double x);

typedef double (*RRFun)(double);


typedef struct {
	RRFun* funcs;
	double x;
	double* res;
	error err_code;
} dataSet;

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
	const double pi = 3.1415926535, eps = 1e-3;
	int test_num, func_num = 4;
	error err;
	double* value;
	value = (double*)malloc(sizeof(double) * func_num);

	dataSet tests[] = {
		{
			(RRFun[]) {sine, cubing, reverseNum, naturalLog},
			pi / 2,
			(double[]) {1.0, 3.87578, 0.63662, 0.451583},
			MALLOC_ERR
		},
		{
			(RRFun[]) {sine, cubing, reverseNum, naturalLog},
			pi / 2,
			(double[]) {1.0, 3.87578, 0.63662, 0.451583},
			OK
		},
		{
			(RRFun[]) {sine, cubing, reverseNum, naturalLog},
			0,
			(double[]) {1.0, 3.87578, 0.63662, 0.451583},
			INCORRECT_ARGUMENT
		},
		{
			(RRFun[]) {sine, cubing, reverseNum, naturalLog},
			-1,
			(double[]) {1.0, 3.87578, 0.63662, 0.451583},
			INCORRECT_ARGUMENT
		}
	};

	test_num = sizeof(tests) / sizeof(tests[0]);

	fillValueArray(tests[0].funcs, -1, tests[0].x, &err);
	if (err == MALLOC_ERR)
		printf("1-й тест пройден :)\n");

	for (int i = 1; i < test_num; i++) {
		value = fillValueArray(tests[i].funcs, func_num, tests[i].x, &err);
		if (err != tests[i].err_code) {
			printf("%d-й тест не пройден :(\n", i + 1);
			continue;
		}
		else if (err == INCORRECT_ARGUMENT || err == MALLOC_ERR) {
			printf("%d-й тест пройден :)\n", i + 1);
			continue;
		}
		else {
			for (int j = 0; j < func_num; j++) {
				if (fabs(value[j] - tests[i].res[j]) > eps) {
					printf("%d-й тест не пройден :(\n", i + 1);
					break;
				}
			}
			printf("%d-й тест пройден :)\n", i + 1);
		}
	}

	return 0;
}