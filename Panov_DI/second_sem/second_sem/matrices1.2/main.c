#include "determ.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {          // Структура тестов:
	const char* input;               // Имя файла
	double res;                      // Результат(ожидаемый)
	error err_code;                  // Код ошибки
} dataSet;

int main(void) {
	int test_num;
	double det, eps = 1e-5;
	error err;

	dataSet tests[] = {
		{
		"mat1.txt",
		14,
		OK
		},
		{
		"mat2.txt",
		-9649,
		OK
		},
		{
		"mat3.txt",
		-6377,
		OK
		},
		{
		"mat4.txt",
		0,
		OK
		}
	};

	test_num = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < test_num; i++) {                                            // Тестирование
		FILE* input;
		double** matrix;
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

		det = calcdet(matrix, n, &err);

		if (err != tests[i].err_code) {
			printf("%d-й тест не пройден.\n", i + 1);
		}
		else if ((err == OK) && (fabs(tests[i].res - det) / 2 > eps)) {
			printf("%d-й тест не пройден.\n", i + 1);
		}
		else {
			printf("%d-й тест пройден.\n", i + 1);
		}
		for (int i = 0; i < n; i++) {
			free(matrix[i]);
		}
		free(matrix);
		fclose(input);
	}

	return 0;
}
