#include <math.h>
#include "z2_3.h"
#include <stdio.h>

typedef struct{  /* новая переменаая-структура для проведения теста */
	RRFun f; //функция №1 
	double a;
    double b; //действительное значение
	double res; //ожидаемый результат
	Error err; //адрес ошибки
} TestCase;

static double parabola(double x); /* Вспомогательная функция для тестирования: константа*/
static double straight_line(double x); /* Вспомогательная функция для тестирования: прибавляет маленькое значение (используется вблизи нуля)*/
static double constanta(double x);  /* Вспомогательная функция для тестирования: прибавляет к действительному числу 1*/
static double power_func(double x); /* Вспомогательная функция для тестирования: вычитает из действительного числа 2*/
static double odd_func(double x); /* Вспомогательная функция для тестирования: нечетная функция*/

static double parabola(double x){
	return ((x * x)+2);
}

static double straight_line(double x){  
	return (x + 3);
}

static double constanta(double x){ 
	x = 2;
	return x;
}
static double power_func(double x){ 
	return pow(x, 4) + 55 * x - 17;
}
static double odd_func(double x){
	return pow(x, 5);
}

int main(void){
	double res, eps = 1e-5;
	Error err;
	
	TestCase tests[] = {{parabola, 1, 3, 12.666667, NA_OK},
	{straight_line, 5, 162, 13580.5, NA_OK},
	{constanta, -4, -0.5, 7, NA_OK},
	{power_func, 4, 1, -1, NA_WRNG_ORD},
	{odd_func, -5, 5, 0, NA_OK}};
	
	int n_tasks = sizeof(tests) / sizeof(tests[0]); /* количество тестов */
	for (int n = 0; n < n_tasks; n++){
		res = Simpson_method(tests[n].f, tests[n].a, tests[n].b, eps, &err);
		if(err != tests[n].err){
			printf("Тест №%d не пройден.\n", n + 1);
		}else if((err == NA_OK) && ((fabs(res - tests[n].res)) > eps)){
			printf("Тест №%d не пройден. %lf\n", n + 1, res);
		}else if((err == NA_OK) && ((fabs(res - tests[n].res)) < eps)){
			printf("Тест №%d успешно пройден. Значение интеграла: %lf\n", n + 1, res);
		}else{
			printf("Тест №%d успешно пройден.\n", n + 1);
		}
	}
	return 0;	
}
