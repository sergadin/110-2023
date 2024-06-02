#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {          // Структура тестов:
	const char* input;               // Имя файла
	error err_code;             // Код ошибки
} dataSet;

int main(void) {
	int test_num;
	error err;

	dataSet tests[] = {
		{
		"input1.txt",
		OK
		},
		{
		"input2.txt",
		OK
		},
		{
		"input3.txt",
		INVALID_MATRIX
		},
		{
		"input4.txt",
		INVALID_MATRIX
		}
	};

	test_num = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < test_num; i++) {                                            // Тестирование
		FILE* input;
		double** matrix, ** inverse_matrix, ** multiplied_matrix = NULL;
		int n;

		if ((input = fopen(tests[i].input, "r")) == NULL) {
			printf("%d-й тест не пройден. Не удалось открыть файл\n", i + 1);
			continue;
		}
		if (fscanf(input, "%d", &n) != 1) {
			printf("%d-й тест не пройден. Ошибка чтения файла\n", i + 1);
			fclose(input);
			continue;
		}

		matrix = (double**)malloc(n * sizeof(double*));
		if (matrix == NULL) {
			printf("%d-й тест не пройден. Память не выделилась\n", i + 1);
			fclose(input);
			continue;
		}
		for (int i = 0; i < n; i++) {
			matrix[i] = (double*)malloc(n * sizeof(double));
			if (matrix[i] == NULL) {
				printf("%d-й тест не пройден. Память не выделилась\n", i + 1);
				fclose(input);
				continue;
			}
		}


		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (fscanf(input, "%lf", &matrix[i][j]) != 1) {
					printf("%d-й тест не пройден. Ошибка чтения файла\n", i + 1);
					fclose(input);
					for (int i = 0; i < n; i++) {
						free(matrix[i]);
					}
					free(matrix);
					continue;
				}
			}
		}

		inverse_matrix = invertMatrix(matrix, n, &err);

		if (err != tests[i].err_code) {
			printf("%d-й тест не пройден :(\n", i + 1);
		}
		else if (err == OK) {
			multiplied_matrix = multiplyMatrices(matrix, inverse_matrix, n, &err);
			printf("\n");
			if (checkMatrix(multiplied_matrix, n) == 1) {
				printf("%d-й тест пройден.\n", i + 1);
				writeMatrix(matrix, n);
		                printf("\n");
                		writeMatrix(inverse_matrix, n);
				printf("\n");
				writeMatrix(multiplied_matrix, n);
			}
			else
				printf("%d-й тест не пройден.\n", i + 1);
		}
		else {
			printf("%d-й тест пройден.\n", i + 1);
		}
		for (int i = 0; i < n; i++) {
			free(matrix[i]);
		}
		free(matrix);
		if (err == OK) {
			for (int i = 0; i < n; i++) {
				free(inverse_matrix[i]);
			}
			free(inverse_matrix);
			for (int i = 0; i < n; i++) {
				free(multiplied_matrix[i]);
			}
			free(multiplied_matrix);
		}
		if (err == INVALID_MATRIX) {
			for (int i = 0; i < n; i++) {
				free(inverse_matrix[i]);
			}
			free(inverse_matrix);
		}
		fclose(input);
	}

	return 0;
}
