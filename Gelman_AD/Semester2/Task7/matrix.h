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
}Error;

double descent_method(double** matrix, int n, double* vector_b, double* vector_x, double epsilon, Error* error);

// Parameters
// *matr - address to the array (original linear representation of the matrix)
// *nmatr - address to the array (new linear representation of the matrix - its minor)
//  n (= order) - dimention of the original matrix (the number of the equasions)
//
// The function solves a system of linear equations using the iterative method of steepest descent
// The Data is entered from a file, the matrix is ​​represented as a single array
//
// Conclusion: If the function executes without errors, the error code OK and the solution of the matrix are returned
// If a memory allocation error occurs, the error code MEMORY_ERROR and the value -1 are returned.
// If an empty matrix is ​​passed (with no values ​​in it), the error code ZERO_MATRIX and the value - 1 are returned.
// If errors occur while working with the file, the function returns the error code FILE_ERROR and the value - 1.
