#include "matrix_1.h"

//Меняем местами i-тую и j-тую строчки
void swap(double *matrix, int n, int m, int i, int j) {
	int x, k;
	for (k=0; k<m; k++) {
		x = matrix[k + m*i];
		matrix[k + m*i] = matrix[k + m*j];
		matrix[k + m*j] = x;
	}
	return;
}

//Вычитание с домножением на коэфф пропорциональности
void sub(double *matrix, int n, int m, int str, int col) {
	int i, j;
	double c;
	
	for (i=str+1; i<n; i++) {
		c = matrix[col + m*i] / matrix[col + m*str];
		for (j=col; j<m; j++) {
			matrix[j + m*i] -= c*matrix[j + m*str];
		}
	}
	return;
}
		
