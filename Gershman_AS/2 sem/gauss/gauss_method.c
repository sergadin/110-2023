#include "gauss_method.h"



static void swapRows(double* mat, int rows, int row_1, int row_2);            // Функция меняет строки местами

static void swapRows(double* mat, int rows, int row_1, int row_2) {
	for (int i = 0; i < rows; i++) {
		double k;
		k = mat[row_1 * rows + i];
		mat[row_1 * rows + i] = mat[row_2 * rows + i];
		mat[row_2 * rows + i] = k;
	}
}


double* gauss_method(double* mat, int m, int n, Error* err) {
	double* res;
	res = (double*)malloc(m * sizeof(double));                           
	if (res == NULL) {
		*err = MEM_ER;
		return 0;
	}

	*err = OK;

	if (m + 1 != n) {                                                    
		*err = NO_SOL;
		return res;
	}



	for (int i = 0; i < m; i++) {                                          // Приведение к верхнетреугольному виду
		double max_element = mat[i * n + i];
		int max_el_in_row = i;
		for (int j = 0; j < m; j++) {
			if (mat[j * n + i] > max_element) {
				max_element = mat[j * n];
				max_el_in_row = j;
			}
		}
		if (i != max_el_in_row)
			swapRows(mat, n, i, max_el_in_row);
		if (mat[i * n + i] == 0) {
			*err = SING_MATR;
			return res;
		}

		for (int j = i + 1; j < m; j++) {
			double l;
			l = mat[j * n + i] / mat[i * n + i];
			for (int k = i; k <= m; k++) {
				mat[j * n + k] -= l * mat[i * n + k];
			}
		}
	}


	for (int i = m - 1; i >= 0; i--) {                                      
		res[i] = mat[i * n + m];
		for (int j = i + 1; j < m; j++) {
			res[i] -= mat[i * n + j] * res[j];
		}
		res[i] /= mat[i * n + i];
	}

	return res;
}
