#include <stdio.h>
#include <math.h>
#include "integral.h"

typedef struct {          // Структура тестов:
	RRFun f;          //   - Указатель на функцию
	double a;         //   - Начало отрезка
	double b;         //   - Конец отрезка
	double res;       //   - Ожидаемый результат
	Error err;        //   - Ожидаемая ошибка
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
	return sin(x);
}

int main(void) {
	int test_num;
	Error err;
	double value;
	const double eps = 1e-5;
	dataSet tests[] = {
		{func1, 0, 2, 10.106667, OK},
		{func2, -10, 5, -217.5, OK},
		{func3, 0, 10, 33.333333, OK},
		{func4, 0, 2.5, 1.80114, OK},
		{func3, 5, 0, 0.803, NO_INTER}
	};

	test_num = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < test_num; i++) {                                            // Тестирование
		value = integral(tests[i].f, tests[i].a, tests[i].b, eps, &err);
		if (err != tests[i].err) {
			printf("%d-й тест не пройден   \n", i + 1);
		}
		else if ((err == OK) && (fabs(tests[i].res - value) / 2 > eps)) {
			printf("%d-й тест не пройден  \n", i + 1);
		}
		else {
			printf("%d-й тест пройден. \n", i + 1);
		}
	}

	return 0;
}
