
#include "./utils/utils.h"

struct testing
{
  const char *File_name;
  int N;
  int M;
  double epsilon;
};

int main (void)
{
  FILE *f = NULL;
  int N = 0;
  int M = 0;
  double *matr = NULL;
  double epsilon = 0;
  struct testing test_number[4] = {
	{"Test1.txt", 2, 2, 0.00001},
	{"Test2.txt", 2, 3, 0.000001},
	{"Test3.txt", 4, 4, 0.00001},
	{"Test4.txt", 5, 4, 0.000001}
  };

  for (int i = 0; i < 4; i++)
	{
	  N = test_number[i].N;
	  M = test_number[i].M;
	  epsilon = test_number[i].epsilon;
	  matr = (double *) malloc ((N * M) * sizeof (double));
	  if (matr == NULL)
		{
		  printf ("Test %d\n Malloc error\n", i + 1);
		  continue;
		}
	  f = fopen (test_number[i].File_name, "r");
	  if (f == NULL)
		{
		  free (matr);
		  printf ("Test %d\n Malloc error", i + 1);
		  continue;
		}
	  for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		  fscanf (f, "%lf", &matr[M * i + j]);
	  fclose (f);
	  printf ("Test %d\n Rang: %d\n", i + 1, rang (N, M, matr, epsilon));
	  free (matr);
	  matr = NULL;
	}

  return 0;
}