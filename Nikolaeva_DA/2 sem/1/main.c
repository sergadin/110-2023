#include <math.h>
#include "sem2.h"
#include <stdio.h>

typedef struct{
	double *funcs;
	double x;
	double y;
	Error error;
} TestCase;

static double constant(doublex);
static double near_to_zero(double x); /* Вспомогательная функция для тестирования: прибавляет маленькое значение (используется вблизи нуля)*/
static double sum_1(double x);  /* Вспомогательная функция для тестирования: прибавляет к действительному числу 1*/
static double substract_2(double x); /* Вспомогательная функция для тестирования: вычитает из действительного числа 2*/
static double substract_2(double x){
	return x - 2;
}

static double constant(double x){  
	return x;
}

static double near_to_zero(double x){  
	return x+=1e-5;
}
static double sum_1(double x){ 
	return x+1;
}
int main(void){
	double y, eps = 1e-7;
	Error error;
	
	TestCase tests[] = {{sin, cos, 0., 1, OK},
	{sin, substract_2, 0.02, 0., infinity},
	{constant, sin, -0.5, 0., infinity},
	{sum_1, near_to_zero, -10000-(1e-6),-(1e-6), OK}};
	
	int n_tasks = sizeof(tests) / sizeof(tests[0]); /* количество тестов */
	for (int n = 0; n < n_tasks; n++){
		y = composing_function(tests[n].*funcs, tests[n].x, eps, &error);
		if(error != tests[n].error){
			printf("Тест №%d не пройден.\n", n+1);
		}else if((error == OK) && (y-tests[n].y) > eps){
			printf("Тест №%d не пройден.\n", n+1);
		}else if((err == OK) && (y-tests[n].y) < eps){
			printf("Тест №%d успешно пройден. Первое подходящее значение у = %lf\n", n+1, y);
		}else{
			printf("Тест №%d успешно пройден.\n", n+1);
		}
	}
	return 0;	
}
