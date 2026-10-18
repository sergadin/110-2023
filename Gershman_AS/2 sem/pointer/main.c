#include "arr_val.h"

double sinus(double x);
double square_trinomial(double x);
double division_two(double x);

typedef struct {
	RRFun* f;
	double x;
	double* res;
	Error err;
} TestCase;

double sinus(double x)
{
	return sin(x);
}

double square_trinomial(double x) {
	return x * x + x + 1;
}

double division_two(double x) {
	return x / 2;
}

int main(void) {
	const double pi = 3.141592653;
	const double eps = 1e-3;
	Error err;
	double* res;

	TestCase tests[] = {
		{
			(RRFun[]) {sinus, square_trinomial, division_two},1,(double[]) {0.841471, 3, 0.5},OK},
{
	(RRFun[]) {sinus, square_trinomial, division_two},0,(double[]) {0.0, 1.0, 0.0},OK},
{
	(RRFun[]) {sinus, square_trinomial, division_two},pi,(double[]) {0, 14.011197, 1.570796},OK}
	};


	for (int i = 0; i < 3; i++) {
		res = arr_of_val(tests[i].f, 3, tests[i].x, &err);
		if (err != tests[i].err) {
			printf("Тест %d не пройден\n", i + 1);
		}
		else if (err == OK) 
		{
			for (int j = 0; j < 3; j++) 
			{
				if (fabs(res[j] - tests[i].res[j]) / 2 > eps) {
					printf("Тест %d не пройден \n", i + 1);
					free(res);
					continue;
				}
				
			}
			printf("Тест %d пройден\n", i + 1);
		}
		else {
			printf("Тест %d пройден \n", i + 1);
		}
	}
	return 0;
}