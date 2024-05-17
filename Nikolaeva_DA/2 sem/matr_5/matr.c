#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "matr.h"

double kvadr_matr(double *matr, int n){
	for(int i = 0; i < n; i++){
		if(matr[i*n + i] == 0){
			return 0;
		}
	}
	return 1;
}
double gauss(double *matr, int n) {
int i, j,k;
    for ( i = 0; i < n; i++) {
        for ( j = i + 1; j < n; j++) {
            double m = matr[j*n + i] / matr[i*n +i];
            for ( k = 0; k < n + 1; k++) {
                matr[j* n + k] -= m * matr[i*n +k];
            }
        }
    }
    return matr[j*n +k];
}
double gauss_o(double *matr, int n) {
int i;
    for (i = n - 1; i >= 0; i--) {
        double sum = matr[i* n + n];
        for (int j = i + 1; j < n; j++) {
            sum -= matr[i*n +j] * matr[j*n + n];
        }
        matr[i*n +n] = sum / matr[i*n + i];
    }
    return matr[i*n + n];
}
// Решение системы линейных уравнений методом простой итерации
int simple_iteration(double *matr, int n, double *x, double tolerance, Error *err) {
    // Проверяем, является ли матрица квадратной
    if (!kvadr_matr(matr, n)) {
       *err = NO_KV;
        return -1;
    }
    // Выделяем память для вектора приближений
    double *x_new = malloc(n * sizeof(double));

    // Инициализируем вектор приближений нулями
    for (int i = 0; i < n; i++) {
        x_new[i] = x[i];
    }
      // Выполняем итерации до тех пор, пока не будет достигнута заданная точность
    int iteration = 0;
    int i;
    double max_error;
    do {
        // Вычисляем новые приближения
        for (int i = 0; i < n ; i++) {
            double sum = matr[i* n +(n - 1)];
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    sum -= matr[i*n + j] * x[j];
                }
            }
            x_new[i] = sum / matr[i*n + i];
          //  printf("%lf  \n",   x_new[i]);
        }
	  double max_error = 0;
        for (int i = 0; i < n; i++) {
            max_error = fmax(max_error, fabs(x_new[i] - x[i]));
        }
        for(int j = 0; j < n; j++)
        {
        x[j] = x_new[j];
        }
        iteration++;
    } while ((max_error > tolerance) && (iteration < 1000));

    // Выводим результаты
    printf("Решение системы линейных уравнений методом простой итерации:\n");
    for (int i = 0; i < n; i++) {
        printf("x%d = %.6lf\n", i + 1, x[i]);
        printf("%lf  ", x[i]);
    }
     printf("Количество итераций: %d\n", iteration);
    // Освобождаем память
    free(x_new);
    return x[i];
}
