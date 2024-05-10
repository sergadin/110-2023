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

static double max(double x, double y, double eps); // функция определения максимума из трёх чисел
// Вспомогательные функции для тестирования:
static double f1_power(double x); //степенная функция
static double f2_parabola(double x); // парабола
static double f3_line(double x); // прямолинейная функция


static double max(double x, double y, double eps) {
	double max_ch;
	if (x > y) {
		max_ch = x;
	}
	else if (y > x) {
		max_ch = y;
	}
	if (eps > max_ch) {
		max_ch = eps;
	}
	return max_ch;
}


static double f1_power(double x) { 
	return (pow(x, 3) + 4);
}

static double f2_parabola(double x) {
	return ((x*x) - 2*x + 1);
}

static double f3_line(double x) {  
	return (x + 9);
}


int main(void){
	double res;
	double eps = 1e-6;
	int kol_iters;
	error err;
	
	test_case tests[] = {
		{f1_power, -3, 3, -1.587401, OK},
		{f2_parabola, 2, 202, 1, NO_ROOT},
		{f2_parabola, 6, 3, 1, DATA_ERR},
		{f3_line, 1e-23, 1e-30, -9, DATA_ERR}};
	
	int n_tests = sizeof(tests) / sizeof(tests[0]); // количество тестов
	
	for (int i = 0; i < n_tests; i++) {
		res = chord_method(tests[i].f, tests[i].a, tests[i].b, eps, &err, &kol_iters);
		if (err != tests[i].err) {
			printf("тест %d не пройден\n", i + 1);
		}
		else if ((err == OK) && ((fabs(res - tests[i].res)) > (max(res, tests[i].res, 1.0) * eps))) {
			printf("тест %d не пройден\n", i + 1);
		}
		else if ((err == OK) && ((fabs(res - tests[i].res)) < (max(res, tests[i].res, 1.0) * eps))) {
			printf("тест %d пройден, приближённо полученный корень = %lf, количество итераций: %d\n", i + 1, res, kol_iters);
		}
		else {
			printf("тест %d пройден \n", i + 1);
		}
	}
	return 0;	
}