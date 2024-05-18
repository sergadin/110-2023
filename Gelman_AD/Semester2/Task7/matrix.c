#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

/*	Параметры: *matr - адрес на массив (исходное линейное представление матрицы)
 *             *nmatr - адрес на массив (новое линейное представление матрицы - ее минора)
 *             n - размерность исходной матрицы
 *             m - столбец, по которому строится минор
 *      Функция переписывает в новый массив минор исходной матрицы порядка n-1.
 */
// define N 3 - количество уравнений

// The function multiplies matrix A by vector x and writes the result to vector result
void mul_matrix_vector(double A[N][N], double x[N], double result[N]);
void mul_matrix_vector(double A[N][N], double x[N], double result[N]) 
{
    for (int i = 0; i < N; i++) 
    {
        result[i] = 0;

        for (int j = 0; j < N; j++) 
        {
            result[i] += A[i][j] * x[j];
        }
    }
}

// The function scalarly multiplies two vectors x and y
double dot_product(double x[N], double y[N]);
double dot_product(double x[N], double y[N]) 
{
    double result = 0;
    for (int i = 0; i < N; i++) 
    {
        result += x[i] * y[i];
    }
    return result;
}

double determinate(double* matrix, int n, double epsilon, Error* error)
{
    double A[N][N] = { {4.0, -1.0, 1.0}, {-1.0, 4.0, -2.0}, {1.0, -2.0, 4.0} }; //матрица коэффициентов
    double b[N] = { 12.0, -1.0, 5.0 }; //правая часть системы
    double x[N] = { 0.0 }; //начальное приближение
    double r[N], p[N], Ap[N], alpha, beta;
    double tol = 1e-6; //заданная точность
    int k = 0;

    while (sqrt(rsnew) > tol && k < 1000) //1000 - ограничение по числу итераций 
    {
        mul_matrix_vector(A, x, Ap); //Ap = A * x
        for (int i = 0; i < N; i++) 
        {
            r[i] = b[i] - Ap[i]; //рассчитываем вектор невязки r = b - A * x
            p[i] = r[i]; //начальное направление поиска
        }

        mul_matrix_vector(A, p, Ap); //Ap = A * p
        double rsold = dot_product(r, r);
        double rsnew;

        for (int i = 0; i < N; i++) 
        {
            alpha = rsold / dot_product(p, Ap); //вычисляем параметр alpha
            for (int j = 0; j < N; j++) 
            {
                x[j] = x[j] + alpha * p[j]; //корректируем решение
                r[j] = r[j] - alpha * Ap[j];
            }
            rsnew = dot_product(r, r);
            if (sqrt(rsnew) < tol) 
            {
                break; //достигнута необходимая точность
            }
            beta = rsnew / rsold; //вычисляем параметр beta
            for (int j = 0; j < N; j++) 
            {
                p[j] = r[j] + beta * p[j]; //новое направление поиска
            }
            rsold = rsnew;
        }
        k++;
    }

    printf("Solution:\n");
    for (int i = 0; i < N; i++) 
    {
        printf("x[%d] = %.5f\n", i, x[i]);
    }
    return 0;
}




















static void new_matr(double* matr, double* nmatr, int n, int m);
static void new_matr(double* matr, double* nmatr, int n, int m)
{
    int j = 0;
    for (int i = n; i < n * n; i++)
    {
        if ((i % n) != m)
        {
            nmatr[j] = matr[i];
            j++;
        }
        else
        {
            continue;
        }
    }
}


/*	Параметры: *matr - указатель на массив, содержащий элементы матрицы
*          n - порядок передаваемой матрицы
*          eps - погрешность.
*         *err - указатель на код ошибки.
* Функция ищет определитель переданной матрицы, рекурсивно сводя ее к поиску определителя матрицы 2х2.
*/
double determinate(double* matr, int n, double eps, Error* err)
{
    double det = 0; //значение определителя
    double* nmatr = NULL; //новая подматрица (минор) порядка n-1 
    int sgn = 1; //знак минора
    *err = NA_OK;

    if (n == 0)
    {
        *err = NA_ZERO_MATR;
        return -1;
    }

    if (n == 1)
    {
        return matr[0];
    }

    if (n == 2)
    {
        return ((matr[0] * matr[3]) - (matr[1] * matr[2]));
    }

    nmatr = (double*)malloc(((n - 1) * (n - 1)) * sizeof(double));

    for (int i = 0; i < n; i++)
    {

        if (nmatr == NULL)
        {
            printf("Оперативная память не выделена\n");
            *err = NA_MEMORY_ERR;
            return -1;
        }

        new_matr(matr, nmatr, n, i);
        det += sgn * matr[i] * determinate(nmatr, n - 1, eps, err);
        sgn *= -1;

    }
    free(nmatr);
    return det;
}