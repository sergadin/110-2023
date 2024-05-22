#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "inverse_matrix.h"

static double f1(double x);
static double f2(double x);

// функция задаёт кубическую параболу

double f1(double x)
{
	return x * x * x;
}

// функция, задающая параболу с корнями 2 и 3

double f2(double x)
{
	return ((x - 2) * (x - 3));
}

typedef struct testcase{
	double a;
	double b;
	int x;
	int y;
	int len;
	double eps;
	ERR exit_err;
} testcase;

int main(void)
{
	ERR err = OK;
	int n;
	FILE *input, *output;
	double **matr, eps = 0.00001;
	input = fopen("input.txt", "r");
	output = fopen("output.txt", "w");
	printf("1");
	fscanf(input, "%d", &n);
	printf("1");
	for (int i = 0; i < n; i++)
	{
		matr[i] = (double *)malloc(n * sizeof(double));
		for (int j = 0; j < n; j++)
		{
			fscanf(input, "%lf", &matr[i][j]);
		}
	}
	inverse_matrix(matr, n, eps, &err);
	fprintf(output, "%d", n);
	for (int i = 0; i < n; i++)
        {
                for (int j = 0; j < n; j++)
                {
                        fprintf(output, "%lf ", matr[i][j]);
                }
		free(matr[i]);
        }
	fclose(input);
	fclose(output);
	return 0;
}
