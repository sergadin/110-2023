#include "Array_of_values.h"

double sine(double x);
double exp (double x);
double squaring(double x);

typedef struct {
	RRFun* f;
	double x;
	double *res;
	error err;
} TestCase;

double sine(double x) {
	return sin(x);
}

double plus(double x) {
	return x + 1;
}

double squaring(double x) {
	return x * x;
}

int main(void){
    const double pi = 3.141592653;
    int t_num;
    int f_num = 3;
    const double eps = 1e-3;
    error err;
	double* value_arr;

	TestCase tests[] = {
		{
			(RRFun[]) {sine, plus, squaring},
			pi / 2,
			(double[]) {1.0, 2.570796 , 2.467401},
			OK
		},
		{
			(RRFun[]) {sine, plus, squaring},
			0,
			(double[]) {0.0, 1.0, 1.0},
			OK
		},
		{
			(RRFun[]) {sine, plus, squaring},
			0.5,
			(double[]) {0.479426 , 1.5, 0.25},
			OK
		}
	};

	t_num = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < f_num; i++) {
		value_arr = arrayOfValues(tests[i].f, f_num, tests[i].x, &err);
		if (err != tests[i].err) {
			printf("%d test ne proiden \n", i + 1);
		}
		else if (err == OK) {
			for (int j = 0; j < t_num; j++) {
				if (fabs(value_arr[j] - tests[i].res[j]) / 2 > eps) {
					printf("%d test ne proiden \n", i + 1);
					free(value_arr);
					continue;
				}
			}
			printf("%d test proiden \n", i + 1);
		}
		else {
			printf("%d test proiden \n", i + 1);
		}
		if (err != PARAM){
			free(value_arr);
		}
	}
	return 0;
}




