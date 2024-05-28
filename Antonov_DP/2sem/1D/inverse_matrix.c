#include <stdio.h>
#include <math.h>
#include "inverse_matrix.h"

static int compRR(double a, double b, double eps);

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MAX3(a, b, c) MAX(MAX((a), (b)), (c))

static int compRR(double a, double b, double eps)
{
        if (fabs(a - b) < eps * MAX3(a, b, 1))
	{
		return 0;
	}
	if (a > b)
	{
		return 1;
	}
	return -1;
}

static int add_str(double **matr, int str1, int str2, int n, double k);

static int add_str(double **matr, int str1, int str2, int n, double k)
{
	for (int i = 0; i < n; i++)
	{
		matr[str2][i] += k * matr[str1][i];
	}
	return 0;
}

static int mult_str(double **matr, int str, int n, double k);

static int mult_str(double **matr, int str, int n, double k)
{
	for (int i = 0; i < n; i++)
	{
		matr[str][i] *= k;
	}
	return 0;
}

static int change_strs(double **matr, int str1, int str2);

static int change_strs(double **matr, int str1, int str2)
{
	double *sub = matr[str1];
	matr[str1] = matr[str2];
	matr[str2] = sub;
}

int inverse_matrix(double **matr, int n, double eps, ERR *err)
{
	double **inv_matr, coef;
	inv_matr = (double **)malloc(n * sizeof(double *));
	int sub_err, main_str;
	for (int i = 0; i < n; i++)
	{
		inv_matr[i] = (double *)malloc(n * sizeof(double));
		for (int j = 0; j < n; j++)
		{
			inv_matr[i][j] = 0;
		}
		inv_matr[i][i] = 1;
	}
	for (int i = 0; i < n; i++)
	{
		sub_err = 1;
		for (int j = i; j < n; j++)
		{
			if (compRR(matr[j][i], 0, eps) != 0)
			{
				sub_err = 0;
				main_str = j;
				break;
			}
		}
		if (sub_err == 1)
		{
			printf("матрица вырожденная");
			*err = E_M;
			return -1;
		}
		coef = (1 / matr[main_str][i]);
		mult_str(matr, main_str, n, coef);
		mult_str(inv_matr, main_str, n, coef);
		for (int j = (main_str + 1); (j % n) != main_str; j++)
		{
			coef = (-1) * matr[j % n][i];
			add_str(matr, main_str, (j % n), n, coef);
			add_str(inv_matr, main_str, (j % n), n, coef);
		}
		change_strs(matr, main_str, i);
		change_strs(inv_matr, main_str, i);
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			matr[i][j] = inv_matr[i][j];
		}
	}
	for (int i = 0; i < n; i++)
        {
                free(inv_matr[i]);
        }
	return 0;
}
