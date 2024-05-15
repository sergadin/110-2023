#include "matrix.h"

void writeMatrix(double* matrix, size_t m, size_t n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printf("%lf ", matrix[i * n + j]);
		}
		printf("\n");
	}
}


double* solution(double* mat, size_t m, size_t n, error* err) {
	*err = OK;

	double* sol;
	sol = (double*)malloc(m * sizeof(double));
	if (sol == NULL) {
		printf("Память не выделилась :(");
		return 0;
	}

	if (m + 1 != n) {
		printf("Система не определена");
		*err = NO_SOLUTION;
		return 0;
	}

	for (int i = 0; i < m; i++) {
		for (int k = i + 1; k < m; k++) {
			double factor = mat[k * n + i] / mat[i * n + i];
			for (int j = i; j <= m; j++) {
				mat[k * n + j] -= factor * mat[i * n + j];
			}
		}
	}

	for (int i = m - 1; i >= 0; i--) {
		sol[i] = mat[i * n + m];
		for (int j = i + 1; j < m; j++) {
			sol[i] -= mat[i * n + j] * sol[j];
		}
		sol[i] /= mat[i * n + i];
	}

	return sol;
}
