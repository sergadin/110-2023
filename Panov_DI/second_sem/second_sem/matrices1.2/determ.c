#include "determ.h"

static void swapRows(double** mat, int row_1, int row_2);            // Функция меняет строки местами

static void swapRows(double** mat, int row_1, int row_2) {
	double* temp;
	temp = mat[row_1];
	mat[row_1] = mat[row_2];
	mat[row_2] = temp;
}


void writeMatrix(double** matrix, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			printf("%26.14lf ", matrix[i][j]);

		printf("\n");
	}
}


double calcdet(double** given_matrix, int n, error* err) {
	const double eps = 1e-14;
	double det = 1, mult;
	int sign = 1;
	double** matrix;
	*err = OK;

	matrix = (double**)malloc(n * sizeof(double*));
	if (matrix == NULL) {
		*err = MEM_ALLOC_ERR;
		return 0;
	}
	for (int i = 0; i < n; i++) {
		matrix[i] = (double*)malloc(n * sizeof(double));
		if (matrix[i] == NULL) {
			*err = MEM_ALLOC_ERR;
			return 0;
		}
	}


	for (int i = 0; i < n; i++)                                  // Копирование матрицы
		for (int j = 0; j < n; j++)
			matrix[i][j] = given_matrix[i][j];


	for (int i = 0; i < n; i++) {                                // Метод Гаусса - Жордано

		if (matrix[i][i] == 0) {
			for (int j = i + 1; j < n; j++) {
				if (matrix[j][i] != 0) {
					swapRows(matrix, n, i, j);
					sign *= -1;
					break;
				}
			}
		}

		double pivot = matrix[i][i];                             // Выбор главного элемента

		if (fabs(pivot) == 0) {
			det = 0;
			printf("Определитель: %lf\n", det);
			return det;
		}

		for (int j = 0; j < n; j++) {                            // Деление строки на значение главного элемента
			matrix[i][j] /= pivot;
			mult = pivot;
		}

		for (int k = 0; k < n; k++) {                            // Обнуление элементов под и над главными элементами
			if (k != i) {
				double factor = matrix[k][i];
				for (int j = 0; j < n; j++) {
					matrix[k][j] -= matrix[i][j] * factor;
				}
			}
		}

		det *= mult * sign;
	}

	for (int i = 0; i < n; i++) {
		free(matrix[i]);
	}
	free(matrix);

	printf("Определитель: %lf\n", det);
	return det;
}
