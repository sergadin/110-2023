#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "iter.h"

Matrix* create_matrix(int n) {
	Matrix *matr = (Matrix*)malloc(sizeof(Matrix));
	if (matr == NULL) {
		return NULL;
	}
	matr->n = n;
	matr->matr = (double*)malloc(n * n * sizeof(double));
	if (matr->matr == NULL) {
		free(matr);
		return NULL;
	}
	matr->b = (double*)malloc(n * sizeof(double)); 
	if (matr->b == NULL) {
		free(matr->matr);
		free(matr);
		return NULL;
	}
	return matr;
}

void free_matrix(Matrix *matr) {
	free(matr->matr);
	free(matr->b); 
	free(matr);
}

void solve_system(Matrix *matr, double *x, double eps, error *err) {
	int n = matr->n;
	double *x_pr = (double*)malloc(n * sizeof(double));
	if (x_pr == NULL) {
		*err = ERR_MEM;
		return; 
	}

	// Проверка диагональной доминантности
	for (int i = 0; i < n; i++) {
		double sum = 0;
		for (int j = 0; j < n; j++) {
			if (i != j) {
				sum += fabs(matr->matr[i * n + j]);
			}
		}
		if (fabs(matr->matr[i * n + i]) < sum) {
			free(x_pr);
			*err = ERR_CONVERGENCE; 
			return; 
		}
	}

	for (int i = 0; i < n; i++) {
		x[i] = 0.0;
		x_pr[i] = 0.0;
	}

	// Итерационный процесс
	int iter = 0;
	double norm;
	do {
		iter++;
		for (int i = 0; i < n; i++) {
			x_pr[i] = x[i];
			x[i] = matr->b[i]; 
			for (int j = 0; j < n; j++) {
				if (i != j) {
					x[i] -= matr->matr[i * n + j] * x_pr[j];
				}
			}
			x[i] /= matr->matr[i * n + i]; // Деление на диагональный элемент
		}

		// Вычисление нормы разности векторов
		norm = 0.0;
		for (int i = 0; i < n; i++) {
			norm += pow(x[i] - x_pr[i], 2);
		}
		norm = sqrt(norm);
	} while (norm > eps);

	*err = ERR_NONE; 
	free(x_pr);
}
