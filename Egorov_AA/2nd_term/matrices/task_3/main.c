#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>


int main() {
	int m, n;
	double** matrix, ** inverse_matrix;
	printf("Введите размер квадратной матрицы NxN:");
	scanf("%d", &n);
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

	free(matrix);
	free(inverse_matrix);
	return 0;
}
