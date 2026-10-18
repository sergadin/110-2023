#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Перечисление ошибок
typedef enum {
	SUCCESS,            // Всё прошло успешно
	NO_SOL,             // Система не имеет решения
	SING_MATRIX,        // Матрица вырожденная
	MEMORY_FAIL         // Ошибка выделения памяти
} error_t;

// Объявление функций
void printMatrix(const double* mat, int rows, int cols);
double* solveSystem(double* mat, int rows, int cols, error_t* status);

// Печать матрицы
void printMatrix(const double* mat, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%lf ", mat[i * cols + j]);
		}
		printf("\n");
	}
}

// Обмен строк матрицы
static void exchangeRows(double* mat, int cols, int row1, int row2) {
	for (int i = 0; i < cols; i++) {
		double tmp = mat[row1 * cols + i];
		mat[row1 * cols + i] = mat[row2 * cols + i];
		mat[row2 * cols + i] = tmp;
	}
}

// Решение системы линейных уравнений
double* solveSystem(double* mat, int rows, int cols, error_t* status) {
	const double epsilon = 1e-12;
	double* solution = (double*)malloc(rows * sizeof(double)); // Выделение памяти под массив решений

	if (solution == NULL) {
		*status = MEMORY_FAIL;
		return NULL;
	}

	*status = SUCCESS;

	// Проверка на количество уравнений и неизвестных
	if (rows + 1 != cols) {
		*status = NO_SOL;
		return solution;
	}

	// Приведение матрицы к верхнетреугольному виду
	for (int i = 0; i < rows; i++) {
		double maxValue = mat[i * cols + i];
		int maxRow = i;

		// Поиск строки с максимальным элементом
		for (int j = i + 1; j < rows; j++) {
			if (fabs(mat[j * cols + i]) > fabs(maxValue)) {
				maxValue = mat[j * cols + i];
				maxRow = j;
			}
		}

		// Обмен строк, если необходимо
		if (i != maxRow) {
			exchangeRows(mat, cols, i, maxRow);
		}

		// Проверка на вырожденность матрицы
		if (fabs(mat[i * cols + i]) < epsilon) {
			*status = SING_MATRIX;
			return solution;
		}

		// Преобразование строк матрицы
		for (int j = i + 1; j < rows; j++) {
			double coeff = mat[j * cols + i] / mat[i * cols + i];
			for (int k = i; k < cols; k++) {
				mat[j * cols + k] -= coeff * mat[i * cols + k];
			}
		}
	}

	// Обратный ход метода Гаусса
	for (int i = rows - 1; i >= 0; i--) {
		solution[i] = mat[i * cols + rows];
		for (int j = i + 1; j < rows; j++) {
			solution[i] -= mat[i * cols + j] * solution[j];
		}
		solution[i] /= mat[i * cols + i];
	}

	return solution;
}
