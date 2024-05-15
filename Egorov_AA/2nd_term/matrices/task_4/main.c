#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {          // Структура тестов:
	char* input;               // Имя файла
	double* res;               // Ожидаемые значения
	error err_code;             // Код ошибки
} dataSet;


int main(void) {
	const double eps = 0.0001;
	int test_num;
	error err;

	dataSet tests[] = {
		{
		"input.txt",
		(double[]) {
 0.28571428, 0.85714285, 7.42857142, -3.57142857
},
OK
},
{
"input2.txt",
(double[]) {
0.28571428, 0.85714285, 7.42857142, -3.57142857
},
OK
},
{
"input2.txt",
(double[]) {
0.28571428, 0.85714285, 7.42857142, -3.57142857
},
OK
}
	};

	test_num = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < test_num; i++) {                                            // Тестирование
		FILE* input;
		error err;
		double* matrix, * sol;
		int m, n;
		if ((input = fopen(tests[i].input, "r")) == NULL) {
			printf("%d-й тест не пройден. Не удалось открыть файл\n", i + 1);
			continue;
		}
		if (fscanf(input, "%d%d", &m, &n) == NULL) {
			printf("%d-й тест не пройден. Ошибка чтения файла", i + 1);
			fclose(input);
			continue;
		}

		matrix = (double*)malloc(m * n * sizeof(double));
		if (matrix == NULL) {
			printf("%d-й тест не пройден. Память не выделилась", i + 1);
			fclose(input);
			continue;
		}

		for (int i = 0; i < m * n; i++) {
			if (fscanf(input, "%lf", &matrix[i]) == NULL) {
				printf("%d-й тест не пройден. Ошибка чтения файла", i + 1);
				fclose(input);
				free(matrix);
				continue;
			}
		}

		sol = solution(matrix, m, n, &err);

		if (err != tests[i].err_code) {
			printf("%d-й тест не пройден :(\n", i + 1);
		}
		else if (err == OK) {
			for (int j = 0; j < m; j++) {
				if (fabs(sol[j] - tests[i].res[j]) > eps * fmax(fabs(sol[j]), fabs(tests[i].res[j]))) {
					printf("%d-й тест не пройден :(\n", i + 1);
					goto theend;
				}
			}
			printf("%d-й тест пройден.\nРешения:", i + 1);
			writeMatrix(sol, 1, m);
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
