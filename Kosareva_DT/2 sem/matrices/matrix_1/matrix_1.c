#include <math.h>
#include <stdio.h>
#include "matrix_1.h"

int rank(double *matrix, int n, int m, double eps) {
	int i, j, rank;
	
	rank = 0;
	for (i=0; i<m; i++) {
		j = rank;
		while ((j<n) && (fabs(matrix[j*m + i])<eps)) {
			j++;
		}
		if (j<n) {
			swap(matrix, n, m, rank, j);
			sub(matrix, n, m, rank, i);
			rank++;
		}
	}
	return rank;
}
