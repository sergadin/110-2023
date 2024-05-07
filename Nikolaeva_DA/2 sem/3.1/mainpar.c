#include <stdio.h>
#include <math.h>
#include "parabola.h"
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

double func1(double x) {
	return 5;
	}


double func2(double x) {
	return 5 * x - 2;
}


double func3(double x) {
	return  x * x;
}


int main(void) {
	int n_tests;
	Error err;
	double value;
	const double eps = 1e-5;
	dataSet tests[] = {                                     //      Тесты
		{func1, -1000, 1000, 5, OK},                   //  Имя функции, 
		{func2, -10, 5, -52, OK},                     //   Начало отрезка,
		{func3, 100, 40, 4900 , NA_INTER}           //   Ожидаемая ошибка
		                              };             
		                                           
		                  

	n_tests = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < n_tests; i++) {                                            // Тестирование
		value = min_parabolic(tests[i].f, tests[i].a, tests[i].b, eps, &err);
		if (err != tests[i].err) {
			printf("%d-й тест не пройден \n", i + 1);
		}
		else if ((err == OK) && (fabs(tests[i].res - value) / 2 > eps)) {
			printf("%d-й тест не пройден \n", i + 1);
		}
		else {
			printf("%d-й тест пройден.\n", i + 1);
		}
	}

	return 0;
}
