#include "gauss.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {          // Структура тестов:
	const char* input;            // Имя файла
	double* res;                  // Ожидаемые значения
	error_t err_code;             // Код ошибки
} dataSet;


int main(void) {
	const double eps = 0.0001;
	int test_num;
	error_t err;

	dataSet tests[] = {
		{
		"mat1.txt",
		(double[]) { 0.28571428, 0.85714285, 7.42857142, -3.57142857 },
		SUCCESS
		},
		{
		"mat2.txt",
		(double[]) { 1000 },
		SUCCESS
		},
		{
		"mat3.txt",
		(double[]) { 55.17704468, -0.35057501, -2.53179109, 55.26782329, -1.04136025, -117.35089055, 5.13566938 },
		SUCCESS
		},
		{
		"mat4.txt",
		(double[]) { 0 },
		NO_SOL
		},
		{
		"mat5.txt",
		(double[]) { 0 },
		SING_MATRIX
		}
	};

	test_num = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < test_num; i++) {                                            // Тестирование
		FILE* input;
		double* matrix, * sol;
		int m, n;
		if ((input = fopen(tests[i].input, "r")) == NULL) {
			printf("%d-й тест не пройден. Не удалось открыть файл\n", i + 1);
			continue;
		}
		if (fscanf(input, "%d%d", &m, &n) != 2) {
			printf("%d-й тест не пройден. Ошибка чтения файла\n", i + 1);
			fclose(input);
			continue;
		}

		matrix = (double*)malloc(m * n * sizeof(double));
		if (matrix == NULL) {
			printf("%d-й тест не пройден. Память не выделилась\n", i + 1);
			fclose(input);
			continue;
		}

		for (int j = 0; j < m * n; j++) {
			if (fscanf(input, "%lf", &matrix[j]) != 1) {
				printf("%d-й тест не пройден. Ошибка чтения файла\n", i + 1);
				fclose(input);
				free(matrix);
				continue;
			}
		}

		sol = solveSystem(matrix, m, n, &err);

		if (err != tests[i].err_code) {
			printf("%d-й тест не пройден.\n", i + 1);
		}
		else if (err == SUCCESS) {
			for (int j = 0; j < m; j++) {
				if (fabs(sol[j] - tests[i].res[j]) > eps * fmax(fabs(sol[j]), fabs(tests[i].res[j]))) {
					printf("%d-й тест не пройден.\n", i + 1);
					goto theend;
				}
			}
			printf("%d-й тест пройден. Решения:", i + 1);
			printMatrix(sol, 1, m);
		}
		else {
			printf("%d-й тест пройден.\n", i + 1);
		}
	theend:
		free(matrix);
		free(sol);
		fclose(input);
	}
	
	return 0;
}
