#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>


int main() {
	int m, n;
	double** matrix, ** inverse_matrix;
	printf("Введите размер квадратной матрицы NxN:");
	scanf("%d", &n);
	m = n;
	matrix = (double**)malloc(n * sizeof(double*));
	for (int i = 0; i < n; i++) {
		matrix[i] = (double*)malloc(n * sizeof(double));
	}
	fillMatrix(&matrix, n, n);

	printf("\nСгенерированная матрица размера %dx%d:\n", n, n);
	writeMatrix(matrix, n, n);

	inverse_matrix = invertMatrix(matrix, n);

	printf("\nОбратная матрица:\n");
	writeMatrix(inverse_matrix, n, n);
	
	for (int i = 0; i < m; i++) {
		free(matrix[i]);
	}
	free(matrix);
	for (int i = 0; i < n; i++) {
		free(inverse_matrix[i]);
	}
	free(inverse_matrix);
	return 0;
}
