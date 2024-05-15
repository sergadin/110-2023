#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Gaussian_method.h"

#define EPS 0.0000001

// Функция меняет в матрице 2 строки местами
void swap_rows(double **matrix, int row1, int row2, int cols)
{
    double *temp;

    if (row1 == row2)
        return;

    temp = (double *)malloc(cols * sizeof(double));

    for (int i = 0; i < cols; i++)
    {
        temp[i] = matrix[row1][i];
    }
    for (int i = 0; i < cols; i++)
    {
        matrix[row1][i] = matrix[row2][i];
    }
    for (int i = 0; i < cols; i++)
    {
        matrix[row2][i] = temp[i];
    }
    free(temp);
}

// функция возвращает максимальный по абсолютному значению элемент в i столбце матрицы
int find_max(double **matrix, int rows, int i)
{
    double max = 0;
    int index = i;
    for (int j = i; j < rows; j++)
    {
        if (fabs(matrix[j][i] > max))
        {
            max = matrix[j][i];
            index = j;
        }
    }
    return index;
}

// Функция делит j строку матрицы на значение temp
void divide(double **matrix, int row, int cols, double temp)
{
    for (int i = 0; i < cols; i++)
    {
        matrix[row][i] /= temp;
    }
}

int is_zero(double x)
{
    if (fabs(x) < EPS)
        return 1;
    return 0;
}

// Функция по ступенчатой матрицей вычисляет столбец решений (фактически обратный ход метода гаусса)
double *get_solutions(double **matrix, int rows, int cols)
{
    double temp = 0;
    double *solutions = (double *)malloc(rows * sizeof(double));
    solutions[rows - 1] = matrix[rows - 1][cols - 1];

    for (int i = rows - 2; i >= 0; i--)
    {
        temp = matrix[i][cols - 1];
        for (int j = i + 1; j < cols - 1; j++)
        {
            temp -= matrix[i][j] * solutions[j];
        }
        solutions[i] = temp;
    }

    return solutions;
}

// Основная функция
double *gauss(double **m_matrix, int rows, int cols, Error *error)
{
    int check_null = 0;
    int max_el_index;
    double temp;
    double *solution;
    double **matrix;
    // Проверка на подходящий размер
    if (rows + 1 != cols)
    {
        *error = SIZE;
        return NULL;
    }
    matrix = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (double *)malloc(cols * sizeof(double));
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = m_matrix[i][j];
        }
    }

    for (int i = 0; i < rows; i++)
    {
        // находим максимальный элемент в столбце
        max_el_index = find_max(matrix, rows, i);

        // ставим строку с этим элементом на 1 место
        swap_rows(matrix, i, max_el_index, cols);

        // делим каждую строку на ее первый элемент
        for (int j = i; j < rows; j++)
        {
            temp = matrix[j][i];
            if (is_zero(temp))
                continue;
            divide(matrix, j, cols, temp);
        }

        // вычитаем первую строку из остальных
        for (int j = i + 1; j < rows; j++)
        {
            if (is_zero(matrix[j][i]))
                continue;
            for (int k = i; k < cols; k++)
            {
                matrix[j][k] -= matrix[i][k];
            }
        }
    }

    for (int i = 0; i < cols - 1; i++)
    {
        if (fabs(matrix[rows - 1][i]) > EPS)
            check_null++;
    }
    if (check_null == 0)
    {
        *error = NOT_DET;
        for (int j = 0; j < rows; j++)
        {
            free(matrix[j]);
        }
        free(matrix);
        return NULL;
    }

    // получаем строку решений
    solution = get_solutions(matrix, rows, cols);
    for (int j = 0; j < rows; j++)
    {
        free(matrix[j]);
    }
    free(matrix);
    *error = OK;
    return solution;
}
