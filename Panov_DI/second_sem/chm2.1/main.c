#include <stdio.h>
#include <math.h>
#include "rectanglemeth.h"

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
	return x * x * x + 50 * x - 102;
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
	int test_num, iteration_num;
	error err;
	double value;
	const double eps = 1e-3;
	dataSet tests[] = {
		{func1, 2, 4, 156, OK},
		{func2, -5, 2, -371, OK},
		{func3, 0, 2.5, 2.0882, OK},
		{func4, 0, 10, 50, OK},
		{func3, 5, 0, 0.803, WRONG_INTERVAL}
	};

	test_num = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < test_num; i++) {                                            // Тестирование
		iteration_num = 0;
		value = countintegral(tests[i].func, tests[i].a, tests[i].b, &iteration_num, &err);
		if (err != tests[i].err_code) {
			printf("%d-й тест не пройден. %d\n", i + 1, iteration_num);
		}
		else if ((err == OK) && (fabs(tests[i].res - value) / 2 > eps)) {
			printf("%d-й тест не пройден. %d\n", i + 1, iteration_num);
		}
		else {
			printf("%d-й тест пройден. Количество итераций - %d\n", i + 1, iteration_num);
		}
	}

	return 0;
}