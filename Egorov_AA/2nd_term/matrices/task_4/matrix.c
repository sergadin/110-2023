#include "matrix.h"

void writeMatrix(double* matrix, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printf("%lf ", matrix[i * n + j]);
		}
		printf("\n");
	}
}


double* solution(double* mat, int m, int n, error* err) {
    const double eps = 0.000000000000;
	double* sol;
	sol = (double*)malloc(m * sizeof(double));                             // Называние массива
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
		for (int j = i + 1; j < m; j++) {
            double factor;
            if (fabs(mat[i * n + i]) > eps) {
                factor = mat[j * n + i] / mat[i * n + i];
            }
            else {
                *err = SINGULAR_MATRIX;
                return sol;
            }   
            
			for (int k = i; k <= m; k++) {
				mat[j * n + k] -= factor * mat[i * n + k];
			}
		}
		if (fabs(mat[i * n + i] ) <= eps && fabs(mat[i * n + m]) >= eps) {
			*err = SINGULAR_MATRIX;
			return sol;
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
