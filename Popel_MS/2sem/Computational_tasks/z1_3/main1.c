#include <math.h>
#include "z1_3.h"
#include <stdio.h>

typedef struct{  /* новая переменаая-структура для проведения теста */
	RRFun f; //функция
	double a; //левая граница
    	double b; //правая граница
	double res; //ожидаемый результат
	Error err; //адрес ошибки
} TestCase;

static double parabola(double x); /* Вспомогательная функция для тестирования: парабола*/
static double straight_line(double x); /* Вспомогательная функция для тестирования: прямолинейная функция - не будет корней*/
static double almost_zero(double x);  /* Вспомогательная функция для тестирования: функция со значениями вблизи нуля*/
static double power_func(double x); /* Вспомогательная функция для тестирования: степенная функция - неправильный порядок параметров*/

static double parabola(double x){
	return ((x * x)-2);
}

static double straight_line(double x){  
	return (x + 3);
}

static double almost_zero(double x){  
	return (100000 * (x - (1e - 6)));
}
static double power_func(double x){ 
	return pow(x, 4) + 55 * x - 17;
}

int main(void){
	double res, eps = 1e-7;
	Error err;
	int iter;
	
	TestCase tests[] = {{parabola, 0.5, 3, 1.414214, NA_OK},
	{straight_line, 5, 162, -1, NA_NO_ROOT},
	{almost_zero, -100000, 5, 1e - 6, NA_OK},
	{power_func, 4, 1, -1, NA_WRNG_ORD}};
	
	int n_tasks = sizeof(tests) / sizeof(tests[0]); /* количество тестов */
	for (int n = 0; n < n_tasks; n++){
		res = chord_method(tests[n].f, tests[n].a, tests[n].b, eps, &err, &iter);
		if(err != tests[n].err){
			printf("Тест №%d не пройден.\n", n + 1);
		}else if((err == NA_OK) && ((fabs(res-tests[n].res)) > eps)){
			printf("Тест №%d не пройден.\n", n + 1);
		}else if((err == NA_OK) && ((fabs(res-tests[n].res)) < eps)){
			printf("Тест №%d успешно пройден. Первое подходящее значение x = %lf. Количество итераций: %d\n", n + 1, res, iter);
		}else{
			printf("Тест №%d успешно пройден.\n", n + 1);
		}
	}
	return 0;	
}
