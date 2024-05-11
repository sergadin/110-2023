
#include "./utils/utils.h"

struct testing
{
  const char *File_name;
  int N;
  int M;
  double epsilon;
};

int
main (void)
{
  FILE *f = NULL;
  int N = 0;
  int M = 0;
  int error_counter = 0;
  double **matr = NULL;
  double epsilon = 0;
  struct testing test_number[4] = 
  {
	{"Test1.txt", 2, 2, 0.00001},
	{"Test2.txt", 2, 3, 0.000001},
	{"Test3.txt", 4, 4, 0.00001},
	{"Test4.txt", 5, 4, 0.000001}
  };
  for (int i = 0; i < 4; i++)
	{
	  matr = NULL;
	  error_counter = 0;
	  N = test_number[i].N;
	  M = test_number[i].M;
	  epsilon = test_number[i].epsilon;
	  matr = (double **) malloc ((N) * sizeof (double *));
	  if (matr == NULL)
		{
		  printf ("Test %d\n Malloc error\n", i + 1);
		  continue;
		}
	  for (int i = 0; i < N; i++)
		{
		  matr[i] = NULL;
		  matr[i] = (double *) malloc ((M) * sizeof (double));
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
		  free (matr);
		  printf ("Malloc error");
		  continue;
		}
	  f = fopen (test_number[i].File_name, "r");
	  if (f == NULL)
		{
		  for (int i = 0; i < N; i++)
			free (matr[i]);
		  free (matr);
		  printf ("Test %d\n File not open", i + 1);
		  continue;
		}
	  for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		  fscanf (f, "%lf", &matr[i][j]);
	  fclose (f);
	  printf ("Test %d\n Rang: %d\n", i + 1, rang (N, M, matr, epsilon));
	  for (int i = 0; i < N; i++)
		free (matr[i]);
	  free (matr);
	}
  return 0;
}