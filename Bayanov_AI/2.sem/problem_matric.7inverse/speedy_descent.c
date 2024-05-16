#include "./utils/utils.h"


static double scalar_product (int n, double *vector_a, double *vector_b)
{
  double scalar_product = 0;
  for (int i = 0; i < n; i++)
	scalar_product += vector_a[i] * vector_b[i];
  return scalar_product;
}
//Функция вычисляет скалярное произведение векторов a и b

static void product_Atx (int N, double *matr, double *vector_x, double *vector_result)
{
  for (int i = 0; i < N; i++)
	{
	  vector_result[i] = 0;
	  for (int j = 0; j < N; j++)
		vector_result[i] += matr[N * j + i] * vector_x[j];
	}
}
//Функция вычисляет произведение транспонированной матрицы A на вектор-столбец x

static void product_Ax (int N, double *matr, double *vector_x, double *vector_result)
{
  for (int i = 0; i < N; i++)
	{
	  vector_result[i] = 0;
	  for (int j = 0; j < N; j++)
		vector_result[i] += matr[N * i + j] * vector_x[j];
	}
}
//Функция вычисляет произведение матрицы A на вектор-стобец x


void speedy_descent (int N, double *matr, double *vector_b, double *vector_x, double epsilon, ERROR * error)
{
  int iterations = 0;
  double m = 0;
  double square_length_AAtr = 0;
  double *vector_r = NULL;
  double *vector_Atr = NULL;
  double *vector_AAtr = NULL;
  double *vector_Ax = NULL;
  vector_r = (double *) malloc ((N) * sizeof (double));
  vector_Atr = (double *) malloc ((N) * sizeof (double));
  vector_AAtr = (double *) malloc ((N) * sizeof (double));
  vector_Ax = (double *) malloc ((N) * sizeof (double));
  for (int i = 0; i < N; i++)
	{
	  vector_r[i] = vector_b[i];
	  vector_x[i] = 0;
	}

  while (sqrt (scalar_product (N, vector_r, vector_r)) >= epsilon && iterations < LIMIT)
	{
	  product_Ax (N, matr, vector_x, vector_Ax);
	  for (int i = 0; i < N; i++)
		{
		  vector_r[i] = vector_Ax[i] - vector_b[i];
		}
	  product_Atx (N, matr, vector_r, vector_Atr);
	  product_Ax (N, matr, vector_Atr, vector_AAtr);
	  square_length_AAtr = scalar_product (N, vector_AAtr, vector_AAtr);
	  if (sqrt (square_length_AAtr) <= epsilon)
		{
		  break;
		  *error = ERROR_Divide_by_zero;
		}
	  m = scalar_product (N, vector_r, vector_AAtr) / square_length_AAtr;
	  for (int i = 0; i < N; i++)
		{
		  vector_x[i] -= m * vector_Atr[i];
		}
	  iterations++;
	}

  if (fabs (scalar_product (N, vector_r, vector_r)) >= epsilon && iterations == LIMIT)
	*error = ERROR_LIMIT;


  free (vector_r);
  free (vector_Atr);
  free (vector_AAtr);
  free (vector_Ax);
}
//Функция ищет столбец решений квадратной и определенной СЛУ методом скорейшего спуска