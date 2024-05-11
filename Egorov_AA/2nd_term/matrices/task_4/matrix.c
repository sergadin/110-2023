#include "matrix.h"

void fillMatrix(int*** matrix, int m, int n) {
	srand(time(NULL));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			(*matrix)[i][j] = rand();
		}
	}
}


void writeMatrix(int** matrix, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}