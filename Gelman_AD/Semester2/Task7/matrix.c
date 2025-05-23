#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

// Parameters
// *matrix - address to the array (original linear representation of the matrix)
//  n (= order) - dimention of the original matrix (the number of the equasions)

// The function multiplies matrix A by vector x and writes the result to vector result
void mul_matrix_vector(double** matrix, int n, double* vector_x, double* result_vector);
void mul_matrix_vector(double** matrix, int n, double* vector_x, double* result_vector)
{
    for (int i = 0; i < n; i++)
    {
        result_vector[i] = 0;

        for (int j = 0; j < n; j++)
        {
            result_vector[i] += matrix[i][j] * vector_x[j];
        }
    }
}

// The function scalarly multiplies two vectors x and y
double dot_product(double* x, double* y, int n);
double dot_product(double* x, double* y, int n)
{
    double result = 0;
    for (int i = 0; i < n; i++)
    {
        result += x[i] * y[i];
    }
    return result;
}

// The function multiplies the transposed matrix A and the column vector x
void mul_trmatrix_vector(double** matrix, int n, double* vector_x, double* result_vector);
void mul_trmatrix_vector(double** matrix, int n, double* vector_x, double* result_vector)
{
    for (int i = 0; i < n; i++)
    {
        result_vector[i] = 0;
        for (int j = 0; j < n; j++)
        {
            result_vector[i] += matrix[j][i] * vector_x[j];
        }
    }
}

void descent_method(double** matrix, int n, double* vector_b, double* vector_x, double epsilon, Error* error)
{
    double* result_vector = NULL;
    double* vector_Ax = NULL;
    double* tr_vector_A = NULL;
    double* vector_AAtr = NULL;
    double square_length_AAtr = 0;
    int limit = 100000; // The limit of the iterations
    int iteration = 0; // The number of iterations
    double k = 0; // The coefficient for Gauss method

    result_vector = (double *) malloc((n) * sizeof (double));
    vector_Ax = (double *) malloc((n) * sizeof (double));
    tr_vector_A = (double *) malloc((n) * sizeof (double));
    vector_AAtr = (double *) malloc((n) * sizeof (double));

    for (int i = 0; i < n; i++)
    {
        result_vector[i] = vector_b[i];
        vector_x[i] = 0;
    }

    while (sqrt (dot_product (result_vector, result_vector, n)) >= epsilon && iteration < limit)
    {
        mul_matrix_vector(matrix, n, vector_x, vector_Ax); // Ap = A * x

        for (int i = 0; i < n; i++)
        {
            result_vector[i] = vector_Ax[i] - vector_b[i];; // Counting vector r = A * x - b
        }

        mul_trmatrix_vector(matrix, n, result_vector, tr_vector_A);
        mul_matrix_vector(matrix, n, tr_vector_A, vector_AAtr);

        square_length_AAtr = dot_product(vector_AAtr, vector_AAtr, n);
        if (sqrt(square_length_AAtr) <= epsilon)
        {
            break;
            *error = ZERO_MATRIX; // Divided by zero
        }

        k = dot_product(result_vector, vector_AAtr, n) / square_length_AAtr;
        for (int i = 0; i < n; i++)
        {
            vector_x[i] -= k * tr_vector_A[i];
        }

        iteration++;
    }
    if (fabs(dot_product(result_vector, result_vector, n)) >= epsilon && iteration == limit)
    {
        *error = ITERATION_LIMIT_EXEEDED;
    }

    free(result_vector);
    free(vector_Ax);
    free(tr_vector_A);
    free(vector_AAtr);
}