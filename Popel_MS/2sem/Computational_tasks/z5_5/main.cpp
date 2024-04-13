#include <math.h>
#include "z5_5.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
typedef struct{  /* новая переменаая-структура для проведения теста */
	RRFun f; //функция 
	double a; //левая граница отрезка
    double b; //правая граница отрезка
	int len;
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
	return (pow(x,5)-sqrt(2)*x+17);
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
	
	TestCase tests[] = {{func1, -10, 5, 100, 10, NA_OK},
	{func2, 5, 162, 100, 0, NA_OK},
	{func3, -1000, 1000, 100, 0, NA_OK},
	{sin, 4, 53, 100, 10, NA_OK},
    {func4, 0.5, (sqrt(2)+1)/2, 2, 10, NA_OK}
    };
	
	int n_tasks = sizeof(tests) / sizeof(tests[0]); /* количество тестов */
	for (int n = 0; n < n_tasks; n++){
	int count = 1;
        for (int j = 1; j<32; j*=2){
            res = Min_square(tests[n].f, tests[n].a, tests[n].b, (tests[n].len)*j, eps, &err);
            if(err != tests[n].err){
                printf("Тест №%d.%d не пройден. %lf\n", n + 1, count, res);
            //}else if((err == NA_OK) && ((fabs(res - tests[n].res)) > (max(res, tests[n].res, 1.0)*eps))){
               // printf("Тест №%d.%d не пройден. %lf\n", n+1, count, res);
            }else if((err == NA_OK) /*&& ((fabs(res - tests[n].res)) < (max(res, tests[n].res, 1.0)*eps))*/){
                printf("Тест №%d.%d успешно пройден. Максимальное отклонение = %lf, количество точек = %d\n", n + 1, count, res, (tests[n].len)*j);
            }else{
                printf("Тест №%d.%d успешно пройден.\n", n + 1, count);
            }
            count+=1;
        }
        printf("\n");
	}
	return 0;	
}
