#include <math.h>
#include "matr.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct{  /* новая переменаая-структура для проведения теста */
	const char * file_name; //название файла, в котором находятся элементы матрицы
	double res; //ожидаемый результат
	Error err; //адрес ошибки
} TestCase;


int main(void){
	double res = 0, eps = 1e-5;
	int n = 0; //порядок матрицы - считывается из файла
	double *matr = NULL; //указатель на массив, содержащий элементы матрицы, переменная для записи результата
	FILE *f = NULL;
	//double matr[i] ;
	Error err;

	TestCase tests[] = {{"matr1.txt", 0, NO_KV},
		{"matr2.txt", 6.5, OK},
		{"matr3.txt", -20, OK},
		{"matr4.txt", 0, OK},
		{"matr5.txt", 356948478124, OK}};

	int n_tasks = sizeof(tests) / sizeof(tests[0]); /* количество тестов */
	for (int k = 0; k < n_tasks; k++){
		f = fopen(tests[k].file_name, "r");
		if (f == NULL){		/*Открытие файла, считывание из него значений элементов матрицы и запись их в массив.*/
			printf("Файл не открывается\n");
			err = FILE_WR;
			goto terminate;
		}

		if (fscanf(f, "%d", &n) != 1){
			printf("Файл пуст\n");
			err = FILE_WR;
			fclose(f);
			goto terminate;
			
		}

		// Вводим размерность системы
	//	int n;
	//	fscanf(f, "%d", &n);

		// Выделяем память для матрицы и вектора правых частей
	        matr = malloc(n * n *sizeof(double));
		if (matr == NULL){
			printf("Оперативная память не выделена\n");
			err = NA_MEMORY_ERR;
			fclose(f);
			goto terminate;
		}
		for (int i = 0; i < n; ++i){
			if (fscanf(f, "%lf", &matr[i])!=1){
				printf("В файле недостаточно значений\n");
				err = FILE_WR;
				free(matr);
				fclose(f);
				goto terminate;
			}
		}

		//for (int i = 0; i < n; i++) {
		// matr[i] = malloc((n + 1) * sizeof(double));
		//}
	        double  *b = malloc(n * sizeof(double));

		// Вводим коэффициенты матрицы и вектор правых частей из файла
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n + 1; j++) {
				fscanf(f, "%lf", &matr[i*n + j]);
			}
		}

		// Вводим начальное приближение из файла
		double  *x = malloc(n * sizeof(double));
		for (int i = 0; i < n; i++) {
			fscanf(f, "%lf", &x[i]);
		}

		// Вводим точность из файла
		double tolerance;
		fscanf(f, "%lf", &tolerance);

		// Закрываем файл
		fclose(f);

		// Решаем систему методом простой итерации
		res = simple_iteration(matr, n, x, tolerance, &err);

		free(matr);
		free(b);
		free(x);
		terminate:
		if(err != tests[k].err){
			printf("Тест №%d не пройден.\n", n + 1);
		}else if((err == OK) && (fabs(res - tests[k].res)) >  eps){
			printf("Тест №%d не пройден. %lf\n", n + 1, res);
		}else if((err == OK) && ((fabs(res - tests[n].res)) <  eps)){
			printf("Тест №%d успешно пройден. Значение  матрицы: %lf\n", n + 1, res);
		}else{
			printf("Тест №%d успешно пройден.\n", n + 1);
		}
	}

		return 0;
	}
