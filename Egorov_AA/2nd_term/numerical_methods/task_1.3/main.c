#include <stdio.h>
#include <math.h>sd
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
	return x * x - 10 * x + 32;
}


double func4(double x) {
	return 5;
}


int main(void) {
	printf("Привет, мир");
	return 0;
}