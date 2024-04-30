#include <math.h>
#include "z5_5.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
typedef struct{  /* новая переменаая-структура для проведения теста */
	RRFun f; //функция 
	double a; //левая граница отрезка
    double b; //правая граница отрезка
	int len; //количество точек х
    double res; //ожидаемый результат
	Error err; //адрес ошибки
	const char * file_name; //название файла
} TestCase;

static double func1(double x); /* Вспомогательная функция для тестирования: степенная функция*/
static double func2(double x); /* Вспомогательная функция для тестирования: наклонная прямая*/
static double func3(double x);  /* Вспомогательная функция для тестирования: константа*/

static double func1(double x){
	return (pow(x,3) - sqrt(2) * x + 17);
}

static double func2(double x){  
	return (x + 3);
}

static double func3(double x){  
	x = 2;
	return x;
}

int main(void){
	double res, eps = 1e-5;
	Error err;
	
	TestCase tests[] = {
	{func3, -1000, 1000, 32, 0, NA_OK, "output1.txt"},
    {sin, -1000, 1000, 32, 10, NA_OK, "output2.txt"},
    {func2, -1000, 1000, 32, 0, NA_OK, "output3.txt"},
    {func1, -30, 90, 32, 10, NA_OK, "output4.txt"}, 
    {cos, 23, -10, 32, 10, NA_WRNG_ORD, "output4.txt"},
    };
	
	int n_tasks = sizeof(tests) / sizeof(tests[0]); /* количество тестов */
	for (int n = 0; n < n_tasks; n++){
	int count = 1;
        for (int j = 1; j < 32; j *= 2){
            res = Min_square(tests[n].f, tests[n].a, tests[n].b, (tests[n].len) * j, eps, &err, tests[n].file_name);
            if(err != tests[n].err){
                printf("Тест №%d.%d не пройден. %lf\n", n + 1, count, res);
            }else if((err == NA_OK)){
                printf("Тест №%d.%d успешно пройден. Максимальное отклонение = %lf, количество точек = %d\n", n + 1, count, sqrt(res), (tests[n].len)*j);
            }else{
                printf("Тест №%d.%d успешно пройден.\n", n + 1, count);
            }
            count+=1;
        }
        printf("\n");
	}
	return 0;	
}
