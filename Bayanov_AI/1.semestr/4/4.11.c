#include <stdio.h>

int Number_of_units (int Number);

int Subsets (int N, int K, FILE * output);

int Number_of_units (int Number)
{
  int counter = 0;
  for (int i = 1; i <= Number; i = i * 2)
    if ((i & Number) != 0)
      counter++;
  return counter;
}

int Subsets (int N, int K, FILE * output)
{
  for (int Number = 1; Number < (1 << N); Number++)
    {
      if (Number_of_units (Number) != K)
	continue;
      fprintf (output, "{ ");
      int position = 0;
      for (int i = 0; i <= N; i++)
	{
	  if ((Number & (1 << i)) != 0)
	    fprintf (output, "%d ", i + 1);
	}
      fprintf (output, "}\n");
    }
  return 1;
}

int main (void)
{
  FILE* output;
  int N;
  int K;
  printf ("Enter N: ");
  scanf ("%d", &N);
  printf ("Enter K: ");
  scanf ("%d", &K);
  output = fopen ("output.txt", "w");
  Subsets (N, K, output);
  fclose (output);
  return 0;
}
