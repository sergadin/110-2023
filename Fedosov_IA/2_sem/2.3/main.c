#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "simpson_integral.h"


typedef struct{  //структура для проведения тестов функции
	int n; //число делений заданного отрезка
	double a; //нижняя граница интегрирования
	double b; //верхняя граница интегрирования
	Rfun f; //действительная функция
	double eps; //погрешность
	double result; //ожидаемыый результат выполнения функции
	Error error; //ошибка
} TestCase;

double linear_function(double x);//просто функция y = x для тестов

int main(void){	
	double result; //результат выполнения основной функции
	Error error; //код ошибки основной функции
	double eps = 1e-8;

	TestCase tests[] = {{10000, -1, 0.2, sin, eps, -0.4397642719, OK}, 
	{10000, 3, 3.5, sin, eps, -0.0535358, OK},
	{10000, -1, 1, linear_function, eps, 0, OK},
	{10000, 1, 10, log, eps, 14.025850929, OK },
	{10000, -10, -3, log, eps, 0, NOT_A_NUMBER}
	};
	
	for (int i = 0; i < 5; i ++) { //i меньше 5 тк всего 5 тестов
		result = simpson_integral(tests[i].n, tests[i].a, tests[i].b, tests[i].f, &error);
		if (error != tests[i].error) {
			printf("Тест %d не пройден\n", i + 1);
		} else if (error == NOT_A_NUMBER) {
			printf("В тесте %d функция не определена на заданном отрезке или в каких-то его точках\n", i + 1);
		} else if (abs(result - tests[i].result) < eps) {
			printf("Тест %d успешно пройден, интеграл равен %lf\n", i + 1, result);
		} else if (!(abs(result - tests[i].result) > eps)) {
			printf("Низкая точность в тесте %d, приближенный ответ %lf\n", i + 1, result);
		}
	}
	
	return 0;	
}

double linear_function(double x) {
	return x;
}
