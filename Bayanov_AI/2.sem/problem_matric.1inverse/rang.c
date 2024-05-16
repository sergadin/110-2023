#include "./utils/utils.h"


static void line_difference (int N, int M, double **matr, int i, int j, double c)
{
  for (int k = 0; k < M; k++)
	{
	  matr[i][k] -= matr[j][k] * c;
	}
}

static void swap (int N, int M, double **matr, int i, int j)
{
  double a = 0;
  for (int k = 0; k < M; k++)
	{
	  a = matr[i][k];
	  matr[i][k] = matr[j][k];
	  matr[j][k] = a;
	}
}

int rang (int N, int M, double **matr, double epsilon)
{
  int rang = 0;
  double leader = 1;
  double repeat_leader = 1;
  int j = 0;
  for (int i = 0; i < M; i++)
	{
	  j = rang;
	  while (j < N)
		{
		  if (fabs (matr[j][i]) < epsilon)
			{
			  j++;
			  continue;
			}
		  leader = matr[j][i];
		  swap (N, M, matr, rang, j);

		  for (int k = j + 1; k < N; k++)
			{
			  repeat_leader = matr[k][i];
			  if (fabs (repeat_leader) > epsilon)
				line_difference (N, M, matr, k, rang, repeat_leader / leader);
			}
		  rang++;
		  break;
		}
	}
  return rang;
}

