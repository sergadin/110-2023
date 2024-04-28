#include <math.h>
#include "z2_2.h"
#include <stdio.h>

typedef struct{  /* новая переменаая-структура для проведения теста */
    const char * file_name; //название файла, в котором находятся элементы матрицы
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
    //double matr1[1] = {4}, matr2[4] = {1, 0.5, -9, 2}, matr3[9] = {1, 2, 3, 3, 2, 1, 4, 2, 5}, *matr4 = NULL;
   // double matr5[36] = {118, 146, 119, 140, 66, 142, 141, 75, 79, 76, 148, 3, 137, 51, 27, 23, 115, 110, 15, 126, 140, 36, 6, 56, 95, 20, 17, 124, 140, 94, 97, 131, 88, 148, 29, 36};
	TestCase tests[] = {{"matr1.txt", 4, NA_OK},
	{"matr2.txt", 6.5, NA_OK},
	{"matr3.txt", -20, NA_OK},
	{"matr4.txt", 0, NA_ZERO_MATR},
    {"matr5.txt", -25986176625338, NA_OK}};
	
	int n_tasks = sizeof(tests) / sizeof(tests[0]); /* количество тестов */
	for (int n = 0; n < n_tasks; n++){
		res = determinant(tests[n].file_name, eps, &err);
		if(err != tests[n].err){
			printf("Тест №%d не пройден.\n", n + 1);
		}else if((err == NA_OK) && ((fabs(res - tests[n].res)) > (max(res, tests[n].res, 1.0) * eps))){
			printf("Тест №%d не пройден. %lf\n", n + 1, res);
		}else if((err == NA_OK) && ((fabs(res - tests[n].res)) < (max(res, tests[n].res, 1.0) * eps))){
			printf("Тест №%d успешно пройден. Значение определителя матрицы: %lf\n", n + 1, res);
		}else{
			printf("Тест №%d успешно пройден.\n", n + 1);
		}
	}
	return 0;	
}
