#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

typedef enum {                      
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
** Перемножаем матрицы и ищем обратную
** !Использовать можно только для квадратных матриц!
**
** Функция создает массив единичной матрицы. С помощью метода Гаусса функция приводит заданную
** матрицу к виду единичной матрицы. Используя те же преобразования на единичной марице, функция
** получает обратную матрицу, адрес на которую она и возвращает, если все прошло без ошибок.
*/
