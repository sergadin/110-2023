#include "matrix.h"

void writeMatrix(double* matrix, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printf("%lf ", matrix[i * n + j]);
		}
		printf("\n");
	}
}


static void swapRows(double* mat, int n, int row_1, int row_2);            // Функция меняет строки местами

static void swapRows(double* mat, int n, int row_1, int row_2) {
	for (int i = 0; i < n; i++) {
		double temp;
		temp = mat[row_1 * n + i];
		mat[row_1 * n + i] = mat[row_2 * n + i];
		mat[row_2 * n + i] = temp;
	}
}


double* solution(double* mat, int m, int n, error* err) {
	const double eps = 0.000000000001;
	double* sol;
	sol = (double*)malloc(m * sizeof(double));                             // Называние масcива
	if (sol == NULL) {
		// printf("Память не выделилась.\n");
		*err = M_ALLOC_ERR;
		return 0;
	}

	*err = OK;

	if (m + 1 != n) {                                                      // Проверка на определенность
		// printf("Система не определена. ");
		*err = NO_SOLUTION;
		return sol;
	}



	for (int i = 0; i < m; i++) {                                          // Приведение к верхнетреугольному виду
		double max_element = mat[i * n + i];
		int row_w_max_el = i;
		for (int j = 0; j < m; j++) {
			if (mat[j * n + i] > max_element) {
				max_element = mat[j * n];
				row_w_max_el = j;
			}
		}
		if (i != row_w_max_el)
			swapRows(mat, n, i, row_w_max_el);
		if (mat[i * n + i] == 0) {
			*err = SINGULAR_MATRIX;
			return sol;
		}

		for (int j = i + 1; j < m; j++) {
			double factor;
			factor = mat[j * n + i] / mat[i * n + i];
			for (int k = i; k <= m; k++) {
				mat[j * n + k] -= factor * mat[i * n + k];
			}
		}
	}


	for (int i = m - 1; i >= 0; i--) {                                      // Заполнение массива значений
		sol[i] = mat[i * n + m];
		for (int j = i + 1; j < m; j++) {
			sol[i] -= mat[i * n + j] * sol[j];
		}
		sol[i] /= mat[i * n + i];
	}

	//writeMatrix(sol, 1, m);

	return sol;
}
