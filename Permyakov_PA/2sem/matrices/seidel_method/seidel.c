#include "seidel.h"

int seidel(double* mat, int n, int m, double** ans, double eps)
{
	double norm = 0;
	double iter = 0;
	double a = mat[0];
	double delta;
	for (int i = 1; i < n; i++){
		iter = 0;
		a = mat[i * (m + 1) + i];
		for (int j = 0; j < m; j++){
			if (fabs(a) < 1e-6){
				return -1;
			}
			iter -= (mat[i * (m + 1) + j] * (*ans)[j] / a);
		}
		iter += mat[i * (m + 1) + m] / a;
		iter += (*ans)[i];
		delta = iter - (*ans)[j];
		norm += delta * delta;
		(*ans)[j] = iter;
	}
	if (sqrt(norm) < eps){
		return 0;
	}
	return seidel(mat, n, m, ans, eps);
}
