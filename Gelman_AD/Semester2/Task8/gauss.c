#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gauss.h"

// Parameters:
// matrix - a pointer to the matrix of pointers to arrays
// m - the number of strings of the matrix
// n - the number of rows of the matrix
// *error - error code pointer
// 
// The function gauss_elimination solves a system of linear equations using the Gaussian elimination method
// With direct pass of the Gaussian method we find the maximum element in column i, 
// Swap the current line with the line containing the maximum element,
// Reduce the main diagonal to unity
// And zero out the elements in column i under the main diagonal. 
// With reverse pass we calculate roots and print the answer


// Function for exchanging two rows of a matrix
static void swap_rows(double* matrix, int n, int row1, int row2);
static void swap_rows(double* matrix, int n, int row1, int row2) 
{
    for (int i = 0; i < n; i++) 
    {
        double temp;
        temp = matrix[row1 * n + i];
        matrix[row1 * n + i] = matrix[row2 * n + i];
        matrix[row2 * n + i] = temp;
    }
}

// Function for printing matrix
void print_matrix(double* matrix, int m, int n)
{
    for (int i = 0; i < m; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            printf("%lf ", matrix[i * n + j]);
        }
        printf("\n");
    }
}

double* gauss_elimination(double* matrix, int m, int n, error* err)
{
    double* solution;
    solution = (double*)malloc(m * sizeof(double));

    if (solution == NULL)
    {
        *err = MEMORY_ERROR;
        return 0;
    }

    *err = OK;

    // Direct pass of the Gaussian method
    for (int i = 0; i < m; i++)
    {
        // Finding the maximum element in column i // m - number of rows
        double max_element = matrix[i * n + i];
        int max_row = i;
        for (int j = 0; j < m; j++)
        {
            if (matrix[j * n + i] > max_element)
            {
                max_element = matrix[j * n];
                max_row = j;
            }
        }

        // Swapping the current line with the line containing the maximum element
        if (i != max_row)
        {
            swap_rows(matrix, n, i, max_row);
        }

        // Zero out the elements in column i under the main diagonal
        for (int j = i + 1; j < m; j++)
        {
            double mul;
            mul = matrix[j * n + i] / matrix[i * n + i];
            for (int k = i; k <= m; k++)
            {
                matrix[j * n + k] -= mul * matrix[i * n + k];
            }
        }
    }

    // Populating an array of values
    for (int i = m - 1; i >= 0; i--)
    {
        solution[i] = matrix[i * n + m];
        for (int j = i + 1; j < m; j++)
        {
            solution[i] -= matrix[i * n + j] * solution[j];
        }
        solution[i] /= matrix[i * n + i];
    }

    return solution;
}