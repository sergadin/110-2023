#include <math.h>
#include "1.3root.h"
#include <stdio.h>

typedef struct {
	func f; //функция
	double a; //левая граница
	double b; //правая граница
	double res; //ожидаемый результат
	error err; //адрес ошибки
} test_case;

// Вспомогательные функции для тестирования:
static double f1_power(double x); //степенная функция
static double f2_parabola(double x); // парабола
static double f3_line(double x); // прямолинейная функция


static double f1_power(double x){ 
	return (pow(x, 3) + 2);
}

static double f2_parabola(double x){
	return ((x*x) - 2*x + 1);
}

static double f3_line(double x){  
	return (x + 9);
}


int main(void){
	double res;
	double eps = 1e-6;
	error err;
	int kol_iters;
	
	test_case tests[] = {
		{f1_power, -3, 3, -1.25992105, OK},
		{f2_parabola, 2, 202, 1, NO_ROOT},
		{f2_parabola, 6, 3, 1, DATA_ERR},
		{f3_line, 1e-23, 1e-30, -9, DATA_ERR}};
	
	int n_tests = sizeof(tests) / sizeof(tests[0]); // количество тестов
	
	for (int i = 0; i < n_tests; i++) {                                            // Тестирование
		kol_iters = 0;
		res = chord_method(tests[i].f, tests[i].a, tests[i].b, eps, &err, &kol_iters);
		if (err != tests[i].err) {
			printf("тест %d не пройден\n", i + 1);
		}
		else if ((err == OK) && (fabs(tests[i].res - res) > eps)) {
			printf("тест %d не пройден\n", i + 1);
		}
		else if ((err == OK) && (fabs(tests[i].res - res) < eps)) {
			printf("тест %d пройден, первое подходящее значение x = %lf, количество итераций: %d\n", i + 1, res, kol_iters);
		}
		else {
			printf("тест %d пройден \n", i + 1);
		}
	}
	return 0;	
}