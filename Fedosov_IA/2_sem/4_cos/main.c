#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "my_cos.h"


typedef struct{  //структура для проведения тестов функции
	double x;
	double eps;
	double result;
} TestCase;



int main(void){	
	double result; //результат выполнения основной функции
	double eps = 0.000001;

	TestCase tests[] = {
		{2, eps, -0.416146836547},
		{-1, eps, 0.5403023059},
		{3, eps, -0.989992496600},
		{10, eps, -0.83907152907},
		
	};
	
	for (int i = 0; i < 4; i ++) { 
		result = my_cos(tests[i].x, tests[i].eps);
		if (result < tests[i].result + eps && result > tests[i].result - eps) {
			printf("тест %d успешно пройден, cos(%lf) = %lf\n", i + 1, tests[i].x, result);
		} else {
			printf("тест %d не пройден, cos = %lf\n", i + 1, result);
		}
	}
	
	return 0;	
}
