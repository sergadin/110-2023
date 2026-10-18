#include "calculate.h"

static void swap(double*** mat, int n, int i, int j)
{
	double elem;
	for (int k = 0; k < n; k++){
		elem = (*mat)[i][k];
		(*mat)[i][k] = (*mat)[j][k];
		(*mat)[j][k] = elem;
	}
}

double calculate(double*** mat, int n, int p, int iter_c)
{
	double res = 0;
	int c = 1;
	if (n == 2) {
		return ((*mat)[0][0] * (*mat)[1][1]) - ((*mat)[0][1] * ((*mat)[1][0]);
	}
	for (int i = 0; i < n; i++){
		c *= -1;
		for (int j = i; j < (n - 1); j++){
			swap(mat, n + iter_c, j, j + 1);
		}
		res += c * p * (*mat)[i][n - 1] * calculate(mat, n - 1, p * (-1), iter_c + 1);
		for (int j = n - 1; j > i; j--){
                        swap(mat, n + iter_c, j, j - 1);
                }
	}
	return res;
}
