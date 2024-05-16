#include <stdio.h>
#include <math.h>
#include "4.taylor_cos.h"

typedef struct {
	double x; //действительное значение
	double res; //ожидаемый результат
	error err; //ожидаемый адрес ошибки
} test_case;

static double max(double x, double y, double eps); // функция определения максимума из трёх чисел


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


int main(void){
	double t_cos; // косинус, посчитанный функцией
	double eps = 1e-6;
	int n_tests; // количество тестов
	error err; 
	
	test_case tests[] = {
		{0.5, 0.877583, OK},
		{2, -0.416147, OK},
		{66, -0.999647, OK},
		{1e7, cos(1e7), OK}};
	
	n_tests = sizeof(tests) / sizeof(tests[0]);
	
	for (int i = 0; i < n_tests; i++) {
		t_cos = count_taylor_cos(tests[i].x, eps, &err);
		if (err != tests[i].err) {
			printf("тест %d не пройден\n", i + 1);
		}
		else if ((err == OK) && ((fabs(t_cos - tests[i].res)) > (max(t_cos, tests[i].res, 1.0) * eps))) {
			printf("тест %d не пройден\n", i + 1);
		}
		else if ((err == OK) && ((fabs(t_cos - tests[i].res)) < (max(t_cos, tests[i].res, 1.0) * eps))) {
			printf("тест %d пройден, приближённо полученное значение косинуса = %lf \n", i + 1, t_cos);
		}
		else {
			printf("тест %d пройден \n", i + 1);
		}
	}
	return 0;	
}