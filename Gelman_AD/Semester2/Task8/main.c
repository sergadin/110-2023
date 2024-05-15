#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gauss.h"

typedef struct 
{  /* новая переменаая-структура для проведения теста */
	const char* file_name; //название файла, содержащего элементы матрицы
	int n; //порядок матрицы
	Error err; //адрес ошибки
} TestCase;



int main(void) 
{
	FILE* f;
	Error err;
	int res = 0;
	double** matr = NULL, eps = 1e-5;

	TestCase tests[] = { {"matr1.txt", 1, NA_OK},
	{"matr2.txt", 2, NA_OK},
	{"matr3.txt", 3, NA_OK},
	{"matr4.txt", 0, NA_ZERO_MATR},
		{"matr5.txt", 6, NA_OK},
	{"matr6.txt", 2, NA_SINGLE_MATR} };

	int n_tasks = sizeof(tests) / sizeof(tests[0]); /* количество тестов */
	for (int n = 0; n < n_tasks; n++) {

		if (tests[n].n == 0) {
			err = NA_ZERO_MATR;
			goto terminate;
		}

		f = fopen(tests[n].file_name, "r"); /*Открытие файла и запись матрицы в массив. "Приписывание" к матрице справа единичной
																										аналогичного порядка.*/
		if (f == NULL) {
			printf("Файл не открывается\n");
			err = FILE_WR;
			goto terminate;
		}
		matr = (double**)malloc(sizeof(double*) * tests[n].n);
		if (matr == NULL) {
			printf("Оперативная память не выделена\n");
			fclose(f);
			err = NA_MEMORY_ERR;
			goto terminate;
		}
		for (int i = 0; i < tests[n].n; i++) {
			matr[i] = (double*)malloc(sizeof(double) * 2 * tests[n].n);
			if (matr[i] == NULL) {
				printf("Оперативная память не выделена\n");
				for (int j = 0; j < i; j++) {
					free(matr[j]);
				}
				free(matr);
				fclose(f);
				err = NA_MEMORY_ERR;
				goto terminate;
			}
			for (int j = 0; j < (2 * tests[n].n); j++) {
				if (j < tests[n].n) {
					if (fscanf(f, "%lf", &matr[i][j]) != 1) {
						printf("В файле недостаточно значений\n");
						err = FILE_WR;
						fclose(f);
						for (int i = 0; i < tests[n].n; i++) {
							free(matr[i]);
						}
						free(matr);
						goto terminate;
					}
				}
				else if (j == tests[n].n + i) {
					matr[i][j] = 1;
				}
				else {
					matr[i][j] = 0;
				}
			}
		}
		fclose(f);

		res = Inverse_matr(matr, tests[n].n, &err, eps);

	terminate:
		if (err != tests[n].err) {
			printf("Тест №%d не пройден.\n", n + 1);
		}
		else if (err == NA_OK) {
			printf("Тест №%d пройден. Обратная матрица:\n\n", n + 1);
			for (int i = 0; i < tests[n].n; i++) {
				for (int j = tests[n].n; j < (2 * tests[n].n); j++) {
					printf("%lf ", matr[i][j]);
				}
				printf("\n");
				free(matr[i]);
			}
			free(matr);
			printf("\n");
		}
		else {
			printf("Тест №%d успешно пройден.\n", n + 1);
		}
	}
	return 0;
}