#include "makearray.h" 

// Функции
double cosine(double x);
double square(double x);
double substract_5(double x);

typedef struct {
	RRFun* funcs;     // Массив указателей на функции
	double x;         // Аргумент
	double* res;      // Массив ожидаемых значений
	error err_code;   // Код ошибки
} dataSet;

double cosine(double x) {
	while ((x > 6.28) || (x < -6.28)) {
		x = x - (3.1415926535 * 2);
	}
	return cos(x);
}

double square(double x) {
	return x * x;
}

double substract_5(double x) {
	return x - 5;
}

int main(void) {
	const double pi = 3.1415926535, eps = 1e-4;
	int test_num, func_num = 3;
	error err;
	double* value;

	dataSet tests[] = {                                             // Tесты
		{
			(RRFun[]) {cosine, square, substract_5},                // Функции      
			pi / 2,									                // Аргумент
			(double[]) {0, 2.467401, -3.429203},                    // Ожидаемые значения
			OK										                // Ожидаемый код ошибки
		},
		{
			(RRFun[]) {cosine, square, substract_5},
			1,
			(double[]) {0.540302 , 1, -4},
			OK
		},
		{
			(RRFun[]) {cosine, square, substract_5},
			10,
			(double[]) {-0.839072, 100, 5},
			OK
		}
	};

	test_num = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < test_num; i++) {
		value = makearray(tests[i].funcs, func_num, tests[i].x, &err);
		if (err != tests[i].err_code) {
			printf("%d-й тест не пройден.\n", i + 1);
		}
		else if (err == OK) {
			for (int j = 0; j < func_num; j++) {
				if (fabs(value[j] - tests[i].res[j]) / 2 > eps) {
					printf("%d-й тест не пройден.\n", i + 1);
					goto endtest;
				}
			}
			printf("%d-й тест пройден.\n", i + 1);
		}
		else {
			printf("%d-й тест пройден.\n", i + 1);
		}

		endtest:
		if (err != MALLOC_ERR)
			free(value);
	}


	return 0;
}
