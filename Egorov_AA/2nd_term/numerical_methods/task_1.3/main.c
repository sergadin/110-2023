#include <stdio.h>
#include <math.h>
#include "findRoot.h"

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
	return x * x - 10 * x + 20;
}


double func4(double x) {
	return 5;
}

int main(void) {
	int test_num, iteration_num;
	error err;
	double value;
	const double eps = 1e-5;
	dataSet tests[] = {                                   //      Тесты
		{func1, -3, 1, -2.110371, OK},                    // { Имя функции, 
		{func2, -10, 5, 0.4, OK},                         //   Начало отрезка,
		{func3, 4, 10, 7.236067, OK},                     //   Конец отрезка,
		{func4, -1000, 1000, 5, WRONG_FUNCTION},          //   Ожидаемое значение,
		{func3, 10, 20, 0.803, WRONG_FUNCTION},           //   Ожидаемая ошибка }
		{func3, 5, 0, 0.803, WRONG_INTERVAL}
	};

	test_num = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < test_num; i++) {                                            // Тестирование
		iteration_num = 0;
		value = findRoot(tests[i].func, tests[i].a, tests[i].b, eps, &iteration_num, &err);
		if (err != tests[i].err_code) {
			printf("%d-й тест не пройден :(  %d\n", i + 1, iteration_num);
		}
		else if ((err == OK) && (fabs(tests[i].res - value) / 2 > eps)) {
			printf("%d-й тест не пройден :(  %d\n", i + 1, iteration_num);
		}
		else {
			printf("%d-й тест пройден. Количество итераций - %d\n", i + 1, iteration_num);
		}
	}

	return 0;
}
