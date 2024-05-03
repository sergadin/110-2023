#include <math.h>
#include "z3_2.h"
#include <stdio.h>

typedef struct{  /* новая переменаая-структура для проведения теста */
	RRFun f; //функция 
	double a; //левая граница отрезка
    double b; //правая граница отрезка
	double res; //ожидаемый результат
	Error err; //адрес ошибки
} TestCase;

static double func1(double x); /* Вспомогательная функция для тестирования: парабола*/
static double func2(double x); /* Вспомогательная функция для тестирования: наклонная прямая*/
static double func3(double x);  /* Вспомогательная функция для тестирования: константа*/
static double func4(double x); /* Вспомогательная функция для тестирования: функция степни 4*/

static double max(double x, double y, double eps);

static double max(double x, double y, double eps){
	double max_1;
	if (x>y){
	max_1 = x;
	}else{
		max_1 = y;
	}
	if (eps>max_1){
		return eps;
	}
	return max_1;
}
static double func1(double x){
	return ((x * x));
}

static double func2(double x){  
	return (x + 3);
}

static double func3(double x){  
	x = 2;
	return x;
}
static double func4(double x){ 
	return pow(x,4) + 55 * x - 17;
}

int main(void){
	double res, eps = 1e-5;
	Error err;
	
	TestCase tests[] = {{func1, -10, 5, 0, NA_OK},
	{func2, 5, 162, 8, NA_OK},
	{func3, -1000, 1000, 100, NA_LIMIT},
	{func4, 4, 1, -1, NA_WRNG_ORD}};
	
	int n_tasks = sizeof(tests) / sizeof(tests[0]); /* количество тестов */
	for (int n = 0; n < n_tasks; n++){
		res = Min_GoldenRatio(tests[n].f, tests[n].a, tests[n].b, eps, &err);
		if(err != tests[n].err){
			printf("Тест №%d не пройден. \n", n + 1);
		}else if((err == NA_OK) && ((fabs(res - tests[n].res)) > (max(res, tests[n].res, 1.0)*eps))){
			printf("Тест №%d не пройден. \n", n+1);
		}else if((err == NA_OK) && ((fabs(res - tests[n].res)) < (max(res, tests[n].res, 1.0)*eps))){
			printf("Тест №%d успешно пройден. Первое подходящее значение x = %lf\n", n + 1, res);
		}else{
			printf("Тест №%d успешно пройден.\n", n + 1);
		}
	}
	return 0;	
}
