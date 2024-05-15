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
		return -1;
	}

	fscanf(input, "%d %d", &m, &n);

	matrix = (double*)malloc(m * n * sizeof(double));

	for (int i = 0; i < m * n; i++) {
		fscanf(input, "%lf", &matrix[i]);
	}

	res = solution(matrix, m, n, &err);

	//writeMatrix(res, 1, m - 1);


	return 0;
}
