#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "inverse_matrix.h"


int main(void)
{
	ERR err = OK;
	int n;
	FILE *input, *output;
	double **matr, eps = 0.00001;
	input = fopen("input.txt", "r");
	output = fopen("output.txt", "w");
	fscanf(input, "%d", &n);
	matr = (double **)malloc(n * sizeof(double *));
	for (int i = 0; i < n; i++)
	{
		matr[i] = (double *)malloc(n * sizeof(double));
		for (int j = 0; j < n; j++)
		{
			fscanf(input, "%lf", &matr[i][j]);
		}
	}
	inverse_matrix(matr, n, eps, &err);
	fprintf(output, "%d ", n);
	for (int i = 0; i < n; i++)
        {
                for (int j = 0; j < n; j++)
                {
                        fprintf(output, "%lf ", matr[i][j]);
                }
		free(matr[i]);
        }
	free(matr);
	fclose(input);
	fclose(output);
	return 0;
}
