#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>


int main() {
	int m, n;
	int** matrix;
	system("chcp 1251");
	printf("Введите размер квадратной матрицы NxN:");
	scanf("%d", &n);
	matrix = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		matrix[i] = (int*)malloc(n * sizeof(int));
	}

	fillMatrix(&matrix, n, n);

	printf("Сгенерированная матрица размера %dx%d:\n", n, n);

	writeMatrix(matrix, n, n);

	return 0;
}
