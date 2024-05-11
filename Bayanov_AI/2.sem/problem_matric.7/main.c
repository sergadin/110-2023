#include "./utils/utils.h"

struct testing
{
  const char *File_name;
  int N;
  double epsilon;
  ERROR error;
};

int main (void)
{
  FILE *f = NULL;
  int N = 0;
  int error_counter = 0;
  double epsilon = 0;
  ERROR error = OK;
  double **matr = NULL;
  double *vector_b = NULL;
  double *vector_x = NULL;
  struct testing test_number[4] = 
  {
	{"Test1.txt", 2, 0.0000001, OK},
	{"Test2.txt", 3, 0.0000001, OK},
	{"Test3.txt", 4, 0.0000001, OK},
	{"Test4.txt", 5, 0.0000001, OK}
  };

  for (int i = 0; i < 4; i++)
	{
	  printf ("\nTest %d\n", i + 1);
	  N = test_number[i].N;
	  epsilon = test_number[i].epsilon;
	  error = OK;
	  vector_b = (double *) malloc ((N) * sizeof (double));
	  if (vector_b == NULL)
		{
		  printf ("Malloc error\n");
		  continue;
		}
	  vector_x = (double *) malloc ((N) * sizeof (double));
	  if (vector_x == NULL)
		{
		  free (vector_b);
		  printf ("Malloc error\n");
		  continue;
		}
	  matr = (double **) malloc ((N) * sizeof (double *));
	  if (matr == NULL)
		{
		  free (vector_b);
		  free (vector_x);
		  printf ("Malloc error\n");
		  continue;
		}
	  for (int i = 0; i < N; i++)
		{
		  matr[i] = NULL;
		  matr[i] = (double *) malloc ((N) * sizeof (double));
		  if (matr[i] == NULL)
			{
			  for (int j = 0; j < i; j++)
				free (matr[j]);
			  error_counter++;
			  break;
			}
		}

	  if (error_counter != 0)
		{
		  free (vector_b);
		  free (vector_x);
		  free (matr);
		  printf ("Malloc error");
		  continue;
		}

	  f = fopen (test_number[i].File_name, "r");
	  if (f == NULL)
		{
		  free (vector_b);
		  free (vector_x);
		  for (int i = 0; i < N; i++)
			free (matr[i]);
		  free (matr);
		  printf ("File open error");
		  continue;
		}
	  for (int i = 0; i < N; i++)
		{
		  for (int j = 0; j < N; j++)
			fscanf (f, "%lf", &matr[i][j]);
		  fscanf (f, "%lf", &vector_b[i]);
		}
	  fclose (f);
	  speedy_descent (N, matr, vector_b, vector_x, epsilon, &error);
	  if (error == ERROR_Divide_by_zero)
		{
		  printf ("During the process, a division by 0 occurred");
		}
	  if (error == ERROR_LIMIT)
		{
		  printf ("The required accuracy was not achieved\n");
		}
	  if (error != ERROR_Divide_by_zero)
		{
		  for (int j = 0; j < N; j++)
			printf ("x%d = %lf ", j + 1, vector_x[j]);
		}
	  free (vector_b);
	  free (vector_x);
	  for (int i = 0; i < N; i++)
		free (matr[i]);
	  free (matr);
	  vector_b = NULL;
	  vector_x = NULL;
	  matr = NULL;
	}
  return 0;
}