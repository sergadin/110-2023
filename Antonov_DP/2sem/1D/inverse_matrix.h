#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef double (*RRFun)(double x);

typedef enum 
{ 
	OK = 0,
       	E_M 	// E_M - матрица вырождена;
} ERR;

// функция находит обратную матрицу с помощью алгебраических дополнений по заданной невырожденной квадратной матрице порядка n с точностью eps.
// матрица задаётся массивом double **matr, порядок int n.

int inverse_matrix(double **matr, int n, double eps, ERR *err);
