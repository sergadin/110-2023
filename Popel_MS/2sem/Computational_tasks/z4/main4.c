#include <math.h>
#include "z4.h"
#include <stdio.h>

typedef struct{  /* новая переменаая-структура для проведения теста */
    double x; //действительное значение - переменная х, в которой ищут значение
	double res; //ожидаемый результат
	Error err; //адрес ошибки
} TestCase;

static double max(double x, double y, double eps);

static double max(double x, double y, double eps){
	double max_1;
	if (x > y){
	max_1 = x;
	}else{
		max_1 = y;
	}
	if (eps > max_1){
		return eps;
	}
	return max_1;
}


int main(void){
	double res, eps = 1e-5;
	Error err;
	
	TestCase tests[] = {{1.69, 1.3, NA_OK},
	{1.9, 1.3784048752, NA_OK},
	{145673, 381.671324571, NA_LIMIT},
	{-5, -1, NA_FORB_VAL}};
	
	int n_tasks = sizeof(tests) / sizeof(tests[0]); /* количество тестов */
	for (int n = 0; n < n_tasks; n++){
		res = Taylor_sqrt(tests[n].x, eps, &err);
		if(err != tests[n].err){
			printf("Тест №%d не пройден.\n", n + 1);
		}else if((err == NA_OK) && ((fabs(res - tests[n].res)) > (max(res, tests[n].res, 1.0) * eps))){
			printf("Тест №%d не пройден.\n", n + 1);
		}else if((err == NA_OK) && ((fabs(res - tests[n].res)) < (max(res, tests[n].res, 1.0) * eps))){
			printf("Тест №%d успешно пройден. Значение функции sqrt: %lf\n", n + 1, res);
		}else{
			printf("Тест №%d успешно пройден.\n", n + 1);
		}
	}
	return 0;	
}
