
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Senior_position (int N);

int Senior_position (int N)
{
  N = abs (N);
  int counter = 0;
  for (int i = 1; (1 << i) <= N; i++)
    {
      if (N & (1 << i) == 0)
	continue;
      counter++;
    }
  return counter + 1;
}

int
main (void)
{
  FILE *output;
  int N;
  printf ("Enter N: ");
  scanf ("%d", &N);
  output = fopen ("output.txt", "w");
  fprintf (output, "The position of the highest bit: %d\n",
	   Senior_position (N));
  fclose (output);
  return 0;
}
