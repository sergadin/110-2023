#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef enum {
	OK,
    NO_INVERSE,
    INCORRECT_SIZE,
    EMPTY_FILE,
}error;

double* Get_Minor(double* matrix, double* minor, int n, int row, int col);
double Get_determinant(double* arr, int n);
double* Get_transpone_matrix(double* arr, int n);
double* Get_stepped(int N, int M, double *matr, double epsilon);
double* Get_reverse(double* arr, int n, double eps, error *err);
double* Matrix_multiplication(double* matrix1, double* matrix2, int size);
void Print_matrix(double* mat,int size);
int Identity_matrix_test(double* mat1,double* mat2, int size, double eps);
void line_difference (int numb_columns, double *matr, int first_number, int second_number, double c);;
void swap (int numb_colums, double *matr, int i, int j);



