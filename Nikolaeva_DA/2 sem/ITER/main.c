#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include "iter.h"

typedef struct {
	const char *file_name;
	double *expected_res;
	error expected_err;
	int expected_size; 
} TestCase;

static double max(double x, double y, double eps) {
	double max_1;
	if (x > y) {
		max_1 = x;
	} else {
		max_1 = y;
	}
	if (eps > max_1) {
		return eps;
	}
	return max_1;
}

int main(void) {
	double eps = 1e-5; 
	int ord = 0;
	double *matr = NULL;
	FILE *f = NULL;
	error err;
	double x[MAX_SIZE];

	TestCase tests[] = {
		{"matr1.txt", (double[]){26/15, 2/3}, ERR_CONVERGENCE, 2},
		{"matr5.txt", (double[]){3, 0.5, 1}, ERR_CONVERGENCE, 3},
		{"matr3.txt", (double[]){  0.243242, -0.216205, 0.810803}, ERR_NONE, 3}
	};
	int n_tasks = sizeof(tests) / sizeof(tests[0]);

	for (int n = 0; n < n_tasks; n++) {
		f = fopen(tests[n].file_name, "r");

		if (f == NULL) {
			printf("Файл не открывается\n");
			err = ERR_MEM;
			goto terminate;
		}

		if (fscanf(f, "%d", &ord) != 1) {
			printf("Файл пуст\n");
			err = ERR_MEM;
			fclose(f);
			goto terminate;
		}

		matr = (double *)malloc((ord * ord) * sizeof(double));
		if (matr == NULL) {
			printf("Оперативная память не выделена\n");
			err = ERR_MEM;
			fclose(f);
			goto terminate;
		}

		for (int i = 0; i < (ord * ord); ++i) {
			if (fscanf(f, "%lf", &matr[i]) != 1) {
				printf("В файле недостаточно значений\n");
				err = ERR_MEM;
				free(matr);
				fclose(f);
				goto terminate;
			}
		}

		Matrix matr_struct;//для свободных членов
		matr_struct.matr = matr;
		matr_struct.n = ord;
		matr_struct.b = (double*)malloc(ord * sizeof(double));
		for (int i = 0; i < ord; ++i) {
			if (fscanf(f, "%lf", &matr_struct.b[i]) != 1) {
				printf("В файле недостаточно значений\n");
				err = ERR_MEM;
				free(matr_struct.matr);
				free(matr_struct.b);
				fclose(f);
				goto terminate;
			}
		}

		fclose(f);
		//Если хотим вывести матрицы и вектор
		printf("Матрица:\n");
		for (int i = 0; i < matr_struct.n; i++) {
			for (int j = 0; j < matr_struct.n; j++) {
				printf("%.2lf ", matr_struct.matr[i * matr_struct.n + j]);
			}
			printf("\n");
		}


		printf("Вектор свободных членов:\n");
		for (int i = 0; i < matr_struct.n; i++) {
			printf("%.2lf\n", matr_struct.b[i]);
		}

		solve_system(&matr_struct, x, eps, &err); 
		free(matr_struct.matr);
		free(matr_struct.b);

terminate:
		// Проверка на соответствие ошибки
		if (err != tests[n].expected_err) {
			printf("Тест №%d не пройден (ошибка не соответствует ожидаемой).\n", n + 1);
			printf("Ожидаемая ошибка: %d\n", tests[n].expected_err);
			printf("Полученная ошибка: %d\n", err);
		} else if (err == ERR_NONE) {
			if (tests[n].expected_size != ord) {
				printf("Тест №%d не пройден (размер решения не соответствует ожидаемому).\n", n + 1);
				printf("Ожидаемый размер: %d\n", tests[n].expected_size);
				printf("Полученный размер: %d\n", ord);
			} else {
				for (int i = 0; i < ord; i++) {
					if (fabs(x[i] - tests[n].expected_res[i]) > max(x[i], tests[n].expected_res[i], 1.0) * eps) {
						printf("Тест №%d не пройден (решение не совпадает с ожидаемым).\n", n + 1);
						printf("Ожидаемое решение:\n");
						for (int j = 0; j < ord; j++) {
							printf("x[%d] = %.6f\n", j, tests[n].expected_res[j]);
						}
						printf("Полученное решение:\n");
						for (int j = 0; j < ord; j++) {
							printf("x[%d] = %.6f\n", j, x[j]);
						}
						break;
					}
				}
				if (err == ERR_NONE) {
					printf("Тест №%d успешно пройден.\n", n + 1);
				}
			}
		} else {
			printf("Тест №%d успешно пройден.\n", n + 1);
		}

		// Вывод решения системы
		if (err == ERR_NONE) {
			printf("Решение системы:\n");
			for (int i = 0; i < matr_struct.n; i++) {
				printf("x[%d] = %.6f\n", i, x[i]);
			}
		}
	}
	return 0;
}
