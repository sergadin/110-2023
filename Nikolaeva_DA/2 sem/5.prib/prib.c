#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prib.h"

// Функция для вычисления интерполяционного многочлена Лагранжа
double lagrange_polynomial(point* xy_points, int qv, double x) {
  double y = 0;
  for (int i = 0; i < qv; i++) {
    double term = xy_points[i].y;
    for (int j = 0; j < qv; j++) {
      if (i != j) {
        term *= (x - xy_points[j].x) / (xy_points[i].x - xy_points[j].x);
      }
    }
    y += term;
  }
  return y;
}

// Функция для интерполяции значений функции

void interpolate(point* xy_points, int qv, point* int_points, int qv_i, double* inter_y, error* err) {
  *err = OK;

  // Проверка на совпадение точек интерполяции
  const double epsilon = 1e-6;

  for (int k = 0; k < qv_i - 1; k++) {
    for (int s = k + 1; s < qv_i; s++) {
      if (fabs(int_points[k].x - int_points[s].x) < epsilon) { // Сравнение с эпсилон
        *err = ERR_INTER_POINTS;
        return;
      }
    }
  }
  // Вычисление значений интерполяционного многочлена
  for (int i = 0; i < qv_i; i++) {
    inter_y[i] = lagrange_polynomial(xy_points, qv, int_points[i].x);
  }
} 

