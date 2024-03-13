#include <math.h>
#include <stdio.h>
#include "is_zero.h"


typedef struct{  //структура для проведения тестов функции
	Rfun f; //функция R -> R
	R_Rfun g; //функция R*R -> Z
	double x; //аргумент f
	double result; //ожидаемыый результат выполнения функции
	Error error; //ошибка
} TestCase;


//функция, возвращающая сумму х и у, округленную вверх до целого числа
int sum_to_int(double x, double y);


//функция, возвращающая произведение х и у, округленное вверх до целого числа
int mult_to_int(double x, double y);


int main(void){	
	int result; //результат выполнения основной функции
	Error error; //код ошибки основной функции

	TestCase tests[] = {{sin, sum_to_int, 0., 2, OK}, 
	{log10, mult_to_int, 10000000000, 3, OK},
	{sqrt, sum_to_int, -5, 0., OP_LIMIT},
	{sqrt, mult_to_int, 20, 0., OP_LIMIT}};
	
	for (int i = 0; i < 4; i ++) { //i меньше 4 тк всего 4 теста
		result = number_when_zero(tests[i].f, tests[i].g, tests[i].x, &error);
		if(error != tests[i].error){
			printf("Ошибка выполнения теста %d\n", i + 1);
		} else if ((error == OK) && (result == tests[i].result)) {
			printf("Тест %d пройден, номера нужных членов последовательности %d и %d \n", i + 1, result - 1, result);
		} else if (error == OP_LIMIT) {
			printf("В тесте %d превышен предел числа операций\n", i + 1);
		}
	}
	
	return 0;	
}


int sum_to_int(double x, double y) {
	return ceil(x + y);
}


int mult_to_int(double x, double y) {
	return ceil(x * y);
}
