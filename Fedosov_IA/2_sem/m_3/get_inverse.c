#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "get_inverse.h"
#define EPS 1e-8

//функция создает матрицу по входному файлу
static double* make_mat(const char *file_name, int* mat_size, Error *error){
  double* mat;
  int size;
  FILE* data = fopen(file_name, "r");
  if (data == NULL) {
    *error = EMPTY_FILE;
    fclose(file_name);
    return;
  }

  if (fscanf(data, "%d", &size) != 1) {
    *error = EMPTY_FILE;
    fclose(file_name);
    return;
  }

  *mat_size = size; 
  mat = (double*)malloc(size * size * sizeof(double));
  for (int i = 0; i < size * size; i ++) {
    fscanf(data, "%lf", &mat[i]);
  }
  fclose(file_name);
  return mat;
}


//функция транспонирования матрицы
static double* transponate(double* mas, int rows, int cols) {
  double* rez;
  rez = (double*)malloc(cols * rows * sizeof(double));

  for (int i = 0; i < cols; i++){
    for (int j = 0; j < rows; j++){
      rez[i * rows + j] = mas[j * rows + i];
    }
  }

  return rez;
}

//функция возвращает матрицу без указанного столбца и строки
static double* get_matr(double* mas, int rows, int cols, int row, int col) {
  int di, dj;

  double* p = (double*)malloc((rows - 1) * (cols - 1) * sizeof(double));
  
  di = 0;
  for (int i = 0; i < rows - 1; i++) {  // проверка индекса строки
    if (i == row) {                     // строка совпала с вычеркиваемой
      di = 1;                           // - дальше индексы на 1 больше
    }   
    dj = 0;
    for (int j = 0; j < cols - 1; j++) {  // проверка индекса столбца
      if (j == col) {                     // столбец совпал с вычеркиваемым
        dj = 1;                           // - дальше индексы на 1 больше
      }
      p[i * (rows - 1) + j] = mas[(i + di) * rows + j + dj];
    }
  }
  return p;
}


//функция рекурсивно вычисляет определитель
static double determinant(double* mas, int m) {
  int k;  
  double* p = 0;
  double d = 0;
  k = 1; //(-1) в степени i

  if (m < 1) {
     printf("Определитель вычислить невозможно!"); 
     return 0;
  }

  if (m == 1) { 
    d = mas[0]; 
    return(d); 
  }

  if (m == 2) { 
    d = mas[0] * mas[m + 1] - (mas[m] * mas[1]); 
    return(d); 
  }

  if (m > 2) {
    for (int i = 0; i < m; i++) {
      p = get_matr(mas, m, m, i, 0);
      d = d + k * mas[i * m] * determinant(p, m - 1);
      k = -k;
    }
  }

  free(p);
  return(d);
}


double* inverse(const char* file, Error* error) {
  int m;
  double* mat = make_mat(file, &m, error);
  if (*error == EMPTY_FILE) {
    return;
  }

  double* rez = (double*)malloc(m * m * sizeof(double));
  double det = determinant(mat, m); // находим определитель исходной матрицы
  if (fabs(det) < EPS) {
    *error = NO_INVERSE;
    return;
  }

  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < m; j++)
    {
      rez[i * m + j] = determinant(get_matr(mat, m, m, i, j), m - 1);
      if ((i + j) % 2 == 1) {       // если сумма индексов строки и столбца нечетная
        rez[i * m + j] = -rez[i * m + j];    // меняем знак минора
      }
      rez[i * m + j] = rez[i * m + j] / det;
    }
  }

  *error = OK;
  return transponate(rez, m, m);
}
















