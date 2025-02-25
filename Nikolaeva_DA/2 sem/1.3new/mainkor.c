#include <stdio.h>
#include <math.h>
#include "kor.h"

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
double func5(double x);

double func1(double x) {
	return ((x * x)-2);
}


double func2(double x) {
	return 5 * x - 2;
}


double func3(double x) {
	return  (100000 * (x - (1e-6)));
}
double func4(double x){  
	return (x + 3);
}


int main(void) {
	int n_tests, max_iter;
	Error err;
	double value;
	const double eps = 1e-5;
	dataSet tests[] = {                                     //      Тесты
		{func1, -0.5, 3, M_SQRT2, OK},                   //  Имя функции, 
		{func2, -10, 5, 0.4, OK},                     //   Начало отрезка,
		{func3, -10000, 5, 1e-6, OK},                //   Конец отрезка,
		{func4, 5, 162, -3, NO_FUNC},               //   Ожидаемое значение,
							    //   Ожидаемая ошибка
	};             

	n_tests = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < n_tests; i++) {                                            // Тестирование
		max_iter = 0;
		value = chord_metod(tests[i].f, tests[i].a, tests[i].b, eps, &max_iter, &err);
		if (err != tests[i].err) {
			printf("%d-й тест не пройден   %d\n", i + 1, max_iter);
		}
		else if ((err == OK) && (fabs(tests[i].res - value) / 2 > eps)) {
			printf("%d-й тест не пройден   %d\n", i + 1, max_iter);
		}
		else {
			printf("%d-й тест пройден. Количество итераций - %d\n", i + 1, max_iter);
		}
	}

	return 0;
}
