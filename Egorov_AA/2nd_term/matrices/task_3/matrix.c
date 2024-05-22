#include "matrix.h"

static void swapRows(double** mat, int n, int row_1, int row_2);            // Функция меняет строки местами

static void swapRows(double** mat, int n, int row_1, int row_2) {
	for (int i = 0; i < n; i++) {
		double temp;
		temp = mat[row_1][i];
		mat[row_1][i] = mat[row_2][i];
		mat[row_2][i] = temp;
	}
}


void fillMatrix(double*** matrix, int n) {
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			(*matrix)[i][j] = rand();
}


void writeMatrix(double** matrix, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			printf("%26.14lf ", matrix[i][j]);

		printf("\n");
	}
}


int checkMatrix(double** matrix, int n) {
	const double eps = 0.00000000001;
	int flag = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) {
				if (matrix[i][j] > 1 + eps)
					flag = 0;
			}
			else {
				if (fabs(matrix[i][j]) > eps)
					flag = 0;
			}
		}
	}
	if (flag)
		return 1;
	else
		return 0;
}


double** multiplyMatrices(double** matrix1, double** matrix2, int n, error* err) {
	double** multiplied_matrix;
	multiplied_matrix = (double**)malloc(n * sizeof(double*));
	if (multiplied_matrix == NULL) {
		printf("Ошибка выделения памяти.");
		*err = MEM_ALLOC_ERR;
		return 0;
	}
	for (int i = 0; i < n; i++) {
		multiplied_matrix[i] = (double*)malloc(n * sizeof(double));
		if (multiplied_matrix[i] == NULL) {
			printf("Ошибка выделения памяти.");
			*err = MEM_ALLOC_ERR;
			return 0;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			multiplied_matrix[i][j] = 0;
			for (int k = 0; k < n; k++) {
				multiplied_matrix[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}

	return multiplied_matrix;
}


double** invertMatrix(double** given_matrix, int n, error* err) {
	const double eps = 0.00000000000001;
	double** inverse_matrix, ** matrix;
	*err = OK;
	inverse_matrix = (double**)malloc(n * sizeof(double*));      // Выделение памяти на матрицы
	if (inverse_matrix == NULL) {
		*err = MEM_ALLOC_ERR;
		return 0;
	}
	for (int i = 0; i < n; i++) {
		inverse_matrix[i] = (double*)malloc(n * sizeof(double));
		if (inverse_matrix[i] == NULL) {
			*err = MEM_ALLOC_ERR;
			return 0;
		}
	}

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

	for (int i = 0; i < n; i++)                                  // Инициализация единичной матрицы
		for (int j = 0; j < n; j++)
			if (i == j)
				inverse_matrix[i][j] = 1;
			else
				inverse_matrix[i][j] = 0;


	for (int i = 0; i < n; i++) {                                // Метод Гаусса - Жордано

		if (matrix[i][i] == 0) {
			for (int j = i + 1; j < n; j++) {
				if (matrix[j][i] != 0) {
					swapRows(matrix, n, i, j);
					swapRows(inverse_matrix, n, i, j);
					break;
				}
			}
		}

		double pivot = matrix[i][i];                             // Выбор главного элемента
	
		if (fabs(pivot) == 0) {
			*err = INVALID_MATRIX;
			return 0;
		}

		for (int j = 0; j < n; j++) {                            // Деление строки на значение главного элемента
			matrix[i][j] /= pivot;
			inverse_matrix[i][j] /= pivot;
		}

		for (int k = 0; k < n; k++) {                            // Обнуление элементов под и над главными элементами
			if (k != i) {
				double factor = matrix[k][i];
				for (int j = 0; j < n; j++) {
					matrix[k][j] -= matrix[i][j] * factor;
					inverse_matrix[k][j] -= inverse_matrix[i][j] * factor;
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		free(matrix[i]);
	}
	free(matrix);

	return inverse_matrix;
}
