#include <stdio.h>
#include <math.h>
#include "findmin.h"

typedef struct {          // Структура тестов:
	RRFun func;           //  функция
	double a;             //  начало отрезка
	double b;             //  конец отрезка
	double res;           //  результат
	error err_code;       //  ошибка
} dataSet;

double func1(double x);
double func2(double x);
double func3(double x);
double func4(double x);


double func1(double x) {
	return x * x + 50 * x + 592;
}


double func2(double x) {
	return 42 * x + 10;
}


double func3(double x) {
	return cos(x) + sin(x) * sin(x);
}


double func4(double x) {
	return 5;
}


int main(void) {
	int test_num;
	error err;
	double value;
	const double eps = 1e-3;
	dataSet tests[] = {                                   //      Тесты
		{func1, -40, 5, -33, OK},
		{func2, -5, 5, -200, OK},
		{func3, -4, -1, -1, OK},
		{func4, -1000, 1000, 5, OK},
		{func3, 5, 0, 0.803, INVALID_INTERVAL},
	};

	test_num = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < test_num; i++) {                                            // Tестирование
		value = findmin(tests[i].func, tests[i].a, tests[i].b, eps, &err);
		if (err != tests[i].err_code) {
			printf("%d-й тест не пройден :(\n", i + 1);
		}
		else if ((err == OK) && (fabs(tests[i].res - value) / 2 > eps)) {
			printf("%d-й тест не пройден :(\n", i + 1);
		}
		else {
			printf("%d-й тест пройден :)\n", i + 1);
		}
	}

	return 0;
}