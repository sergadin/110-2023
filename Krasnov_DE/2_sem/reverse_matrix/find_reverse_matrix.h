#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef enum {
	OK,             //no mistakes
    NO_INVERSE,     //there is no inverse matrix
    EMPTY_FILE,     //this file does not exist
}error;

double* Get_Minor(double* matrix, int n, int row, int col);
double Get_determinant(double* arr, int n);
double* Get_transpone_matrix(double *arr, int n);
double* Get_reverse_matrix(double *arr, int n,double eps, error *err);


