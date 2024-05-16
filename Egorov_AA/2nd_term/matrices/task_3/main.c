#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>


int main(void) {
	int n;
	double** matrix, ** inverse_matrix, ** multiplied_matrix;
	system("chcp 1251");
	printf("Введите размер квадратной матрицы NxN:");
	scanf("%d", &n);
	matrix = (double**)malloc(n * sizeof(double*));
	for (int i = 0; i < n; i++) {
		matrix[i] = (double*)malloc(n * sizeof(double));
	}
	fillMatrix(&matrix, n);

	printf("\nСгенерированная матрица размера %dx%d:\n", n, n);
	writeMatrix(matrix, n);

	inverse_matrix = invertMatrix(matrix, n);

	printf("\nОбратная матрица:\n");
	writeMatrix(inverse_matrix, n);

	multiplied_matrix = multiplyMatrices(matrix, inverse_matrix, n);

	printf("\nРезультат перемножения:\n");

	writeMatrix(multiplied_matrix, n);

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
	return 0;
}
