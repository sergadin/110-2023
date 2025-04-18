#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "get_inverse.h"
#define EPS 1e-8


// функция транспонирования матрицы
static double *transponate(double *mas, int rows, int cols)
{
  double *rez;
  rez = (double *)malloc(cols * rows * sizeof(double));

  for (int i = 0; i < cols; i++)
  {
    for (int j = 0; j < rows; j++)
    {
      rez[i * rows + j] = mas[j * rows + i];
    }
  }

  return rez;
}

// функция возвращает матрицу без указанного столбца и строки
static double *get_matr(double *mas, int rows, int cols, int row, int col)
{
  int di, dj;

  double *p = (double *)malloc((rows - 1) * (cols - 1) * sizeof(double));

  di = 0;
  for (int i = 0; i < rows - 1; i++)
  { // проверка индекса строки
    if (i == row)
    {         // строка совпала с вычеркиваемой
      di = 1; // - дальше индексы на 1 больше
    }
    dj = 0;
    for (int j = 0; j < cols - 1; j++)
    { // проверка индекса столбца
      if (j == col)
      {         // столбец совпал с вычеркиваемым
        dj = 1; // - дальше индексы на 1 больше
      }
      p[i * (rows - 1) + j] = mas[(i + di) * rows + j + dj];
    }
  }
  return p;
}

// функция рекурсивно вычисляет определитель
static double determinant(double *mas, int m)
{
  int k;
  double *p = 0;
  double d = 0;
  k = 1; //(-1) в степени i

  /*if (m < 1)
  {
    printf("Определитель вычислить невозможно!");
    return 0;
  }
  */
  if (m == 1)
  {
    d = mas[0];
    // free(p);
    return (d);
  }

  if (m == 2)
  {
    d = mas[0] * mas[m + 1] - (mas[m] * mas[1]);
    free(p);
    return (d);
  }

  if (m > 2)
  {
    for (int i = 0; i < m; i++)
    {
      p = get_matr(mas, m, m, i, 0);
      d = d + k * mas[i * m] * determinant(p, m - 1);
      k = -k;
      free(p);
    }
  }

  return (d);
}

double *inverse(double* mat, int size, Error *error)
{
  double *temp;
  double *temp2;
  int m = size;
  if (*error == EMPTY_FILE)
  {
    free(mat);
    return 0;
  }

  double *rez = (double *)malloc(m * m * sizeof(double));
  double det = determinant(mat, m); // находим определитель исходной матрицы
  if (fabs(det) < EPS)
  {
    free(rez);
    free(mat);
    *error = NO_INVERSE;
    return 0;
  }

  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < m; j++)
    {
      temp = get_matr(mat, m, m, i, j);
      rez[i * m + j] = determinant(temp, m - 1);
      if ((i + j) % 2 == 1)
      {                                   // если сумма индексов строки и столбца нечетная
        rez[i * m + j] = -rez[i * m + j]; // меняем знак минора
      }
      rez[i * m + j] = rez[i * m + j] / det;
      free(temp);
    }
  }

  free(mat);
  *error = OK;
  temp2 = transponate(rez, m, m);
  free(rez);
  return temp2;
}
