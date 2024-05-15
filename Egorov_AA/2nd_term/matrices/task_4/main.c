#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE* input;
	error err;
	double* matrix, * res;
	int m, n;
	if ((input = fopen("input.txt", "r")) == NULL) {
		printf("Не удалось открыть файл\n");
		return 0;
	}
	if (fscanf(input, "%d %d", &m, &n) == NULL) {
		printf("Ошибка чтения файла :(");
		return 0;
	}

	matrix = (double*)malloc(m * n * sizeof(double));
	if (matrix == NULL) {
		printf("Память не выделилась :(");
		return 0;
	}

	for (int i = 0; i < m * n; i++) {
		if (fscanf(input, "%lf", &matrix[i]) == NULL) {
			printf("Ошибка чтения файла :(");
			return 0;
		}
	}

	res = solution(matrix, m, n, &err);

	writeMatrix(res, 1, m);


	return 0;
}
