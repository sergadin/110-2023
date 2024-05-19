#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum 
{
    OK,
    ZERO_MATRIX,
    MEMORY_ERROR,
    FILE_ERROR,
}Error;

int gauss_elimination(double** matrix, int n, Error* error, double epsilon);

// Parameters:
// **matrix - a pointer to the matrix of pointers to arrays;
// n - the dimention of the matrix
// *error - error code pointer
// 
// The function gauss_elimination solves a system of linear equations using the Gaussian elimination method
// The function executed the code without errors - the error code OK, (value 0), is returned.