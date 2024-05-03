#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "bisection.h"


typedef struct{  //структура для проведения тестов функции
	Rfun f; //функция R -> R
	double a;
	double b;
	double eps;
	double result; //ожидаемыый результат выполнения функции
	Error error; //ошибка
} TestCase;



int main(void){	
	double result; //результат выполнения основной функции
	Error error; //код ошибки основной функции
	double eps = 1e-8;

	TestCase tests[] = {{sin, -1, 0.2, eps, 0, OK}, 
	{sin, 3, 3.5, 0.001, 3.1415, OK},
	{sqrt, 10, 20, eps, 0, SAME_SIGNS},
	{log10, -2, -1, eps, 0, OP_LIMIT},
	};
	
	for (int i = 0; i < 4; i ++) { //i меньше 4 тк всего 4 теста
		result = bisection(tests[i].f, tests[i].eps, tests[i].a, tests[i].b, &error);
		if (error != tests[i].error){
			printf("Тест %d не пройден\n", i + 1);
		} else if (error == OK && abs(result - tests[i].result) < eps) {
			printf("Тест %d пройден, корень уравнения: %lf\n", i + 1, result);
		} else if (error == OP_LIMIT) {
			printf("В тесте %d превышен предел числа операций\n", i + 1);
		} else if (error == SAME_SIGNS) {
			printf("В тесте %d функция не монотонна или не имеет корней на отрезке\n", i + 1);
		}
	}
	
	return 0;	
}


