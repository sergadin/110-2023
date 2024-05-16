// 2.4 вычислить интеграл от данной функциии f(x) на данном отрезке [a,b] с заданной точностью eps  по составной формуле Гаусса (двухточечной)
// использовать алгоритм удвоения сетки и алгоритм автоматического выбора шага. Сравнить с точным ответом
#include <math.h>
#include "2.4integ.h"
#include <stdio.h>

typedef struct {
	func f; //функция
	double a; //действительное значение
	double b; //действительное значение
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
	return ((x*x) + 3);
}

static double f3_line(double x) {  
	return (x + 9);
}


int main(void){
	double res;
	double eps = 1e-6;
	error err;
	
	test_case tests[] = {
		{f1_power, -3, 3, 24, OK},
		{f1_power, 6, 2, -336, DATA_ERR},
		{f2_parabola, 1, 3, 14.6666667, OK},
		{f3_line, 2, 5, 37.5, OK}};
	
	int n_tests = sizeof(tests) / sizeof(tests[0]); // количество тестов
	
	for (int i = 0; i < n_tests; i++) {
		res = integration_gauss(tests[i].f, tests[i].a, tests[i].b, eps, &err);
		if (err != tests[i].err) {
			printf("тест %d не пройден\n", i + 1);
		}
		else if ((err == OK) && ((fabs(res - tests[i].res)) > (max(res, tests[i].res, 1.0) * eps))) {
			printf("тест %d не пройден\n", i + 1);
		}
		else if ((err == OK) && ((fabs(res - tests[i].res)) < (max(res, tests[i].res, 1.0) * eps))) {
			printf("тест %d пройден, приближённо полученный интеграл = %lf \n", i + 1, res);
		}
		else {
			printf("тест %d пройден \n", i + 1);
		}
	}
	return 0;	
}