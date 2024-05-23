#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum {
	OK,
    LIMIT,
    EMPTY_FILE,
    INCORRECT_SIZE,
    INCORRECT_ARG
}error;

double* Get_system_solution(double** mat,double* B_col,double* solution,int size,double eps,error *err);
double** Matrix_multiplication(double** matrix,double** transpone_matrix, int size);
double* Get_matrix_times_vector(double** matrix, double* vector, double* result, int size);
double** Get_transpone_matrix(double** matrix, double** transpone_matrix, int size);
double Get_scalar_product(double* vector1,double* vector2,int size);
double* Get_vector_difference(double* vector1, double* vector2, double* result, int size);
double* Get_vector_number(double* vector,double number,int size);


