#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef double (*RRFun)(double x);

typedef enum 
{ 
	OK = 0,
       	E_M 	// E_M - матрица вырождена;
} ERR;

// функция решает систему линейных уравнений с невырожденной матрицей коэффициентов matr, где значения уравнений записаны в массиве *b.
// n - размер матрицы и количество уравнений.
// eps - точность.
// также нужно ввести массив типа double *val, в котором будут записаны найденные значения.

int solv_lin_equations(double **matr, int n, double *b, double *val, double eps, ERR *err);
