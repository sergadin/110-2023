#include <stdio.h>
#include <math.h>
#include "Matrix_2D.h"


static int comp_r_p_to_zero(double *r_p, int n, double eps);

static int comp_r_p_to_zero(double *r_p, int n,double eps)
{
	int result = 0;
	for (int i = 0; i < n; i++)
	{
		if (fabs(r_p[i]) < eps)
		{
			result++;
		}
	}
	return result;
}

static double find_mu_p(double **matr, double *r_p, int n);

static double find_mu_p(double **matr, double *r_p, int n)
{
	double num = 0, denom = 0, term;
	for (int i = 0; i < n; i++)
	{
		term = 0;
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				term += (matr[i][j] * matr[k][j] * r_p[k]); 
			}
		}
		num += term * r_p[i];
		denom += term * term;
	}
	return (num / denom);
}

static int find_r_p(double **matr, double *r_p, double *b, double *val, int n);

static int find_r_p(double **matr, double *r_p, double *b, double *val, int n)
{
	for (int i = 0; i < n; i++)
	{
		r_p[i] = (-1) * b[i];
		for (int j = 0; j < n; j++)
		{
			r_p[i] += matr[i][j] * val[j];
		}
	}
	return 0;
}

static int find_next_val(double **matr, double *val, double *r_p, double mu, int n);

static int find_next_val(double **matr, double *val, double *r_p, double mu, int n)
{
	for (int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			val[i] += ((-1) * (mu * matr[j][i] * r_p[j]));
		}
	}
	return 0;
}

int solv_lin_equations(double **matr, int n, double *b, double *val, double eps, ERR *err)
{
	double *r_p, mu;
	r_p = (double *)malloc(n * sizeof(double));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (fabs(matr[i][j]) > eps)
			{
				val[i] = (b[i] / matr[i][j]);
				break;
			}
		}
	}
	find_r_p(matr, r_p, b, val, n);
	while (comp_r_p_to_zero(r_p, n, eps) != n)
	{
		mu = find_mu_p(matr, r_p, n);
		find_next_val(matr, val, r_p, mu, n);
		find_r_p(matr, r_p, b, val, n);
	}
	free(r_p);
	return 1;
}
