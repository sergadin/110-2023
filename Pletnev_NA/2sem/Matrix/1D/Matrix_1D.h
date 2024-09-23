#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum
{
    OK,
    ZERO_MATRIX,
    MEMORY_ERROR,
    FILE_ERROR,
    ITERATION_LIMIT_EXEEDED,
} Error;

// Функция решает систему линейных уравнений итерационным методом наискорейшего спуска
// Данные вводятся из файла, матрица представлена ​​одним массивом

void descent_method(double** matrix, int n, double* vector_b, double* vector_x, double epsilon, Error* error);

// Параметры:
// *matr - адрес массива (исходное линейное представление матрицы)
// *nmatr - адрес массива (новое линейное представление матрицы - ее минор)
//  n (= order) - размерность исходной матрицы (количество уравнений)