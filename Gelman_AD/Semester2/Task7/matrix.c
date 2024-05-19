#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

// Parameters
// *matr - address to the array (original linear representation of the matrix)
// *nmatr - address to the array (new linear representation of the matrix - its minor)
//  n (= order) - dimention of the original matrix (the number of the equasions)

// The function multiplies matrix A by vector x and writes the result to vector result
void mul_matrix_vector(double A[n][n], double x[n], double result[n]);
void mul_matrix_vector(double A[n][n], double x[n], double result[n]) 
{
    for (int i = 0; i < n; i++) 
    {
        result[i] = 0;

        for (int j = 0; j < n; j++) 
        {
            result[i] += A[i][j] * x[j];
        }
    }
}

// The function scalarly multiplies two vectors x and y
double dot_product(double x[n], double y[n]);
double dot_product(double x[n], double y[n]) 
{
    double result = 0;
    for (int i = 0; i < n; i++) 
    {
        result += x[i] * y[i];
    }
    return result;
}

double descent_method(double* matrix, int n, double* vector_b, double* vector_x, double epsilon, Error* error)
{
    double A[N][N] = matrix;
    double b[N] = vector_b;
    double x[n] = vector_x;
    double r[n], p[n], Ap[n], alpha, beta;
    int limit = 1000;
    int k = 0;
    *error = OK;

    if (n == 0)
    {
        *error = ZERO_MATRIX;
        return -1;
    }

    while (sqrt(rsnew) > epsilon && k < limit)
    {
        mul_matrix_vector(A, x, Ap); // Ap = A * x
        for (int i = 0; i < n; i++) 
        {
            r[i] = b[i] - Ap[i]; // Counting vector r = b - A * x
            p[i] = r[i]; // Initial search direction
        }

        mul_matrix_vector(A, p, Ap); // Ap = A * p
        double rsold = dot_product(r, r);
        double rsnew;

        for (int i = 0; i < n; i++) 
        {
            alpha = rsold / dot_product(p, Ap); // Calculate the alpha parameter
            for (int j = 0; j < n; j++) 
            {
                x[j] = x[j] + alpha * p[j]; // Adjusting the solution
                r[j] = r[j] - alpha * Ap[j];
            }
            rsnew = dot_product(r, r);
            if (sqrt(rsnew) < epsilon) 
            {
                break; // The required accuracy has been achieved
            }

            beta = rsnew / rsold; // Calculate the beta parameter
            for (int j = 0; j < n; j++) 
            {
                p[j] = r[j] + beta * p[j]; // New search direction
            }
            rsold = rsnew;
        }
        k++;
    }

    printf("Solution:\n");
    for (int i = 0; i < n; i++) 
    {
        printf("x[%d] = %.5f\n", i, x[i]);
    }
    return 0;
}