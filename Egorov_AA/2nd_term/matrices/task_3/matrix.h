#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

typedef enum {                      // Коды ошибок:
	OK,                             //  Все хорошо
	MEM_ALLOC_ERR,                  //  Ошибка выделения памяти
	INVALID_MATRIX,                //  Вырожденная матрица
} error;

void fillMatrix(double*** matrix, int n);

void writeMatrix(double** matrix, int n);

int checkMatrix(double** matrix, int n);

double** multiplyMatrices(double** matrix1, double** matrix2, int n, error* err);

double** invertMatrix(double** given_matrix, int n, error* err);

/*
** Функция заполнения матрицы рандомными числами.
** На вход подается адрес массива, по которому записана матрица, количество столбцов(строк).
**
** Функция вывода массива в консоль.
** На вход подается массив матрицы, количество столбцов(строк).
**
** Функция перемножения матриц.
** Ну вход подается массив левой матрицы, массив правой матрицы, количество столбцов(строк) и код ошибки.
**
** Функция поиска обратной матрицы.
** На вход подается матрица, количество столбцов(строк) и код ошибки.
**
** Функции рассчитаны на квадратные матрицы!
**
** Первые три функции работают понятно, остановимся на четвертой.
** Функция создает массив единичной матрицы. С помощью метода Гаусса-Жордано функция приводит заданную
** матрицу к виду единичной матрицы. Используя те же преобразования на единичной марице, функция
** получает обратную матрицу, адрес на которую она и возвращает, есои все прошло без ошибок.
*/
