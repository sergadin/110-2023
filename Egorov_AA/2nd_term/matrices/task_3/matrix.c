#include "matrix.h"

void fillMatrix(double*** matrix, int m, int n) {
	srand(time(NULL));
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			(*matrix)[i][j] = (double)rand();
}


void writeMatrix(double** matrix, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			printf("%26.14lf ", matrix[i][j]);

		printf("\n");
	}
}


double** invertMatrix(double** matrix, int n) {
	double** inverse_matrix;
	inverse_matrix = (double**)malloc(n * sizeof(double*));
	for (int i = 0; i < n; i++)
		inverse_matrix[i] = (double*)malloc(n * sizeof(double));

	for (int i = 0; i < n; i++)                               // Инициализация единичной матрицы
		for (int j = 0; j < n; j++)
			if (i == j)
				inverse_matrix[i][j] = 1;
			else
				inverse_matrix[i][j] = 0;

	for (int i = 0; i < n; i++) {                             // Метод Гаусса - Жордано
	
		double pivot = matrix[i][i];                      // Выбор главного элемента
		if (pivot == 0.0) {
			printf("Обратная матрица не существует.\n");
			return 0;
		}
		
		for (int j = 0; j < n; j++) {                     // Деление строки на значение главного элемента
			matrix[i][j] /= pivot;
			inverse_matrix[i][j] /= pivot;
		}
		
		for (int k = 0; k < n; k++) {                     // Обнуление элементов под и над главными элементами
			if (k != i) {
				double factor = matrix[k][i];
				for (int j = 0; j < n; j++) {
					matrix[k][j] -= matrix[i][j] * factor;
					inverse_matrix[k][j] -= inverse_matrix[i][j] * factor;
				}
			}
		}
	}

	return inverse_matrix;
}
