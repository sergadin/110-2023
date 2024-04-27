#include <stdio.h>
#include <math.h>
#include "findMinValue.h"

typedef struct {          // Структура тестов:
	RRFun func;           //   - Указатель на функцию
	double a;             //   - Начало отрезка
	double b;             //   - Конец отрезка
	double res;           //   - Ожидаемый результат
	error err_code;       //   - Ожидаемая ошибка
} dataSet;

double func1(double x);      // Заданные функции
double func2(double x);
double func3(double x);
double func4(double x);


double func1(double x) {
	return x * x * x + (x / 5 - 5) * (x / 5 - 5) - 20;
}


double func2(double x) {
	return 5 * x - 2;
}


double func3(double x) {
	return x * x - 10 * x + 32;
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
		{func1, -0.5, 5, 3.938, OK},                      // { Имя функции, 
		{func2, -10, 5, -52, OK},                         //   Начало отрезка,
		{func3, -10, 10, 7, OK},                          //   Конец отрезка,
		{func3, 5, 0, 0.803, WRONG_INTERVAL},             //   Ожидаемое значение,
		{func4, -1000, 1000, 5, OK}                       //   Ожидаемая ошибка }
	};

	test_num = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < test_num; i++) {                                            // Само тестирование
		value = findMinValue(tests[i].func, tests[i].a, tests[i].b, eps, &err);
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