#include <math.h>
#include "matrix_6.h"
#include <stdio.h>

int solve(double **matrix, int n, double eps, double *v) {
	int i, j;
	int count = 0;
	double x;
	double diff = 1;
	
	for (i=0; i<n; i++) {
		v[i] = 0;
	}
	
	while ((diff > eps) && (count < 10000)) {
		diff = 0;
		for (i=0; i<n; i++) {
			x = matrix[i][n];
			for (j=0; j<n; j++) {
				if (j != i) {
					x -= v[j]*matrix[i][j];
				}
			}
			x /= matrix[i][i];
			
			diff += fabs(v[i] - x);
			v[i] = x;
		}
		count++;
	}
	if (count == 10000) {
		return -1;
	}
	for (i=0; i<n; i++) {
		if (isnan(v[i]) || isinf(v[i])) {
			return -1;
		}
	}
	
	return 0;
}
