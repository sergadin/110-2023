#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gauss.h"

// Parameters:
// **matrix - a pointer to the matrix of pointers to arrays;
// n - the dimention of the matrix
// *error - error code pointer
// 
// The function gauss_elimination solves a system of linear equations using the Gaussian elimination method
// With direct pass of the Gaussian method we find the maximum element in column i, 
// Swap the current line with the line containing the maximum element,
// Reduce the main diagonal to unity
// And zero out the elements in column i under the main diagonal. 
// With reverse pass we calculate roots and print the answer


// Function for exchanging two rows of a matrix
void swap_rows(double** matrix, int row1, int row2, int n);
void swap_rows(double** matrix, int row1, int row2, int n) 
{
    for (int i = 0; i < n + 1; i++) 
    {
        double temp = matrix[row1][i];
        matrix[row1][i] = matrix[row2][i];
        matrix[row2][i] = temp;
    }
}

// Function for printing matrix
void print_matrix(double** matrix, int n);
void print_matrix(double** matrix, int n) 
{
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n + 1; j++) 
        {
            printf("%.2f\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int gauss_elimination(double** matrix, int n, Error* error, double epsilon)
{
    *error = OK;

    // Direct pass of the Gaussian method
    for (int i = 0; i < n; i++) 
    {
        // Finding the maximum element in column i
        double max_element = matrix[i][i];
        int max_row = i;
        for (int k = i + 1; k < n; k++) 
        {
            if (matrix[k][i] > max_element) 
            {
                max_element = matrix[k][i];
                max_row = k;
            }
        }

        // Swapping the current line with the line containing the maximum element
        swap_rows(matrix, i, max_row, n);

        // Reducing the main diagonal to unity
        double divide_element = matrix[i][i];
        for (int k = i; k < n + 1; k++) 
        {
            matrix[i][k] /= divide_element;
        }

        // Zero out the elements in column i under the main diagonal
        for (int k = i + 1; k < n; k++) 
        {
            double mul = matrix[k][i];
            for (int j = i; j < n + 1; j++) 
            {
                matrix[k][j] -= mul * matrix[i][j];
            }
        }
    }

    // Reverse pass to calculate roots
    double x[n];
    for (int i = n - 1; i >= 0; i--) 
    {
        x[i] = matrix[i][n];
        for (int j = i + 1; j < n; j++) 
        {
            x[i] -= matrix[i][j] * x[j];
        }
    }

    // Printing the solution
    printf("Solution:\n");
    for (int i = 0; i < n; i++) 
    {
        printf("x%d = %.2f\n", i + 1, x[i]);
    }
    printf("Initial matrix:\n");
    print_matrix(matrix, n);
}