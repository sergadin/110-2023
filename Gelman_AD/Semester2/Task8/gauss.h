#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum 
{
    OK,
    ZERO_MATRIX,
    MEMORY_ERROR,
    FILE_ERROR,
}error;

double* gauss_elimination(double* matrix, int m, int n, error* err);
void print_matrix(double* matrix, int m, int n);

// Parameters:
// matrix - a pointer to the matrix of pointers to arrays
// m - the number of strings of the matrix
// n - the number of rows of the matrix
// *error - error code pointer
// 
// The function gauss_elimination solves a system of linear equations using the Gaussian elimination method
// The function executed the code without errors - the error code OK, (value 0), is returned.