#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "iter.h"

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

  // Инициализация начального приближения
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
      x[i] = matr->matr[i * (n + 1) + n]; // Извлечение свободного члена
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
