#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {          // Структура тестов:
	const char* input;               // Имя файла
	error err_code;             // Код ошибки
} dataSet;

int main() {
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
		OK
		},
		{
		"input4.txt",
		INVALID_MATRIX
		}
	};

	test_num = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < test_num; i++) {                                            // Тестирование
		FILE* input;
		double** matrix, ** inverse_matrix, ** multiplied_matrix;
		int n;
        
        if ((input = fopen(tests[i].input, "r")) == NULL) {
        printf("%d-й тест не пройден. Не удалось открыть файл\n", i + 1);
        continue;
        }
        if (fscanf(input, "%d%", &n) != 1) {
            printf("%d-й тест не пройден. Ошибка чтения файла\n", i + 1);
            fclose(input);
            continue;
        }

        matrix = (double**)malloc(n * sizeof(double*));
        for (int i = 0; i < n; i++) {
            matrix[i] = (double*)malloc(n * sizeof(double));
        }
        
// 		if (matrix == NULL) {
// 			printf("%d-й тест не пройден. Память не выделилась\n", i + 1);
// 			fclose(input);
// 			continue;
// 		}
// 
// 		for (int i = 0; i < m * n; i++) {
// 			if (fscanf(input, "%lf", &matrix[i]) != 1) {
// 				printf("%d-й тест не пройден. Ошибка чтения файла\n", i + 1);
// 				fclose(input);
// 				free(matrix);
// 				continue;
// 			}
// 		}
		
		inverse_matrix = invertMatrix(matrix, n);

		multiplied_matrix = multiplyMatrices(matrix, m, n, &err);

		if (err != tests[i].err_code) {
			printf("%d-й тест не пройден :(\n", i + 1);
		}
		else if (err == OK) {
			if (checkMatrix(multiplied_matrix) == 1)
                printf("%d-й тест пройден.\n", i + 1);
            else
                printf("%d-й тест не пройден.\n", i + 1);
		}
		else {
			printf("%d-й тест пройден.\n", i + 1);
		}
	theend:
        for (int i = 0; i < n; i++) {
            free(matrix[i]);
        }
        free(matrix);
        for (int i = 0; i < n; i++) {
            free(inverse_matrix[i]);
        }
        free(inverse_matrix);
        for (int i = 0; i < n; i++) {
            free(multiplied_matrix[i]);
        }
        free(multiplied_matrix);
        }
	

	return 0;
}
