#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "inverse_matrix.h"

static int check_inv(double **matr, double **inv_matr, int n, double eps);

static int check_inv(double **matr, double **inv_matr, int n, double eps)
{
	double elem;
	for (int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			elem = 0;
			for (int k = 0; k < n; k++)
			{
				elem = elem + (matr[i][k] * inv_matr[k][j]);
			}
			if ((i == j) && (fabs(elem - 1) > eps))
			{
				return 1;
			}
			if((i != j) && (fabs(elem) > eps))
			{
				return 1;
			}
		}
	}
	return 0;
}

int main(void)
{
	ERR err = OK;
	int n;
	FILE *input, *output;
	double **matr, **sub_matr, eps = 0.00001;
	input = fopen("input.txt", "r");
	output = fopen("output.txt", "w");
	fscanf(input, "%d", &n);
	matr = (double **)malloc(n * sizeof(double *));
	sub_matr = (double **)malloc(n * sizeof(double *));
	for (int i = 0; i < n; i++)
	{
		matr[i] = (double *)malloc(n * sizeof(double));
		sub_matr[i] = (double *)malloc(n * sizeof(double));
		for (int j = 0; j < n; j++)
		{
			fscanf(input, "%lf", &matr[i][j]);
			sub_matr[i][j] = matr[i][j];
		}
	}
	inverse_matrix(matr, n, eps, &err);
	if(check_inv(sub_matr, matr, n, eps) == 0)
	{
		printf("матрица действительно обратная");
	}
	else
	{
		printf("к сожалению матрица не обратная");
	}
	fprintf(output, "%d ", n);
	for (int i = 0; i < n; i++)
        {
                for (int j = 0; j < n; j++)
                {
                        fprintf(output, "%lf ", matr[i][j]);
                }
		free(matr[i]);
		free(sub_matr[i]);        
	}
	free(matr);
	free(sub_matr)
;	fclose(input);
	fclose(output);
	return 0;
}
