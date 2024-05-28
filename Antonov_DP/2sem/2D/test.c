#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "solv_lin_equations.h"


int main(void)
{
	ERR err = OK;
	int n;
	FILE *input, *output;
	double **matr, *val, *b, eps = 0.000001;
	input = fopen("input.txt", "r");
	output = fopen("output.txt", "w");
	fscanf(input, "%d", &n);
	val = (double *)malloc(n * sizeof(double));
	b = (double *)malloc(n * sizeof(double));
	matr = (double **)malloc(n * sizeof(double *));
	for (int i = 0; i < n; i++)
	{
		matr[i] = (double *)malloc(n * sizeof(double));
		for (int j = 0; j < n; j++)
		{
			fscanf(input, "%lf", &matr[i][j]);
		}
	}
	for (int i = 0; i < n; i++)
        {
                fscanf(input, "%lf", &b[i]);
        }
	solv_lin_equations(matr, n, b, val, eps, &err);
	fprintf(output, "%d ", n);
	for (int i = 0; i < n; i++)
        {
                fprintf(output, "%lf ", val[i]);
        }
	for (int i = 0; i < n; i++)
	{
                free(matr[i]);
        }
	free(matr);
	free(val);
	free(b);
	fclose(input);
	fclose(output);
	return 0;
}
