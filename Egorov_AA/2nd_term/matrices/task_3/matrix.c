#include "matrix.h"

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


double** multiplyMatrices(double** matrix1, double** matrix2, int n) {
	double** multiplied_matrix;
	multiplied_matrix = (double**)malloc(n * sizeof(double*));
	for (int i = 0; i < n; i++)
		multiplied_matrix[i] = (double*)malloc(n * sizeof(double));

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


double** invertMatrix(double** given_matrix, int n) {
	double** inverse_matrix, ** matrix;
	inverse_matrix = (double**)malloc(n * sizeof(double*));      // Выделение памяти на матрицы
	for (int i = 0; i < n; i++)
		inverse_matrix[i] = (double*)malloc(n * sizeof(double));
	matrix = (double**)malloc(n * sizeof(double*));
	for (int i = 0; i < n; i++)
		matrix[i] = (double*)malloc(n * sizeof(double));

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

		double pivot = matrix[i][i];                             // Выбор главного элемента
		if (fabs(pivot) < 0.0000001) {
			printf("Обратная матрица не существует.\n");
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
