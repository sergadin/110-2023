#include <stdio.h>
#include <math.h>
int different_numbers_counter (FILE * input);

int different_numbers_counter (FILE * input)
{
  int curr, prev, count;
  count = 0;
  if (fscanf (input, "%d", &curr) != 1)
  {
    return -1;}
  count ++;  
  prev = curr;
  while (!feof (input))
    {
      if (fscanf (input, "%d", &curr) == 0)
      {
	return -1;}
      if (prev > curr)
	{
	  return -1;
	}
      if (prev < curr)
	{
	  count ++;
	  prev = curr;
	}
    }
  fclose (input);
  return count;
}

int
main (void)
{
  FILE *input;
  int ans;
  input = fopen ("input.txt", "r");
  if (input == NULL)
    {
      printf ("Error: could not open the file");
      return -1;
    }

  ans = different_numbers_counter (input);
  if (ans == -1)
    printf ("Error: the sequence does not meet the condition");
  if (ans > 0)
    printf ("%d", ans);
  return 0;
}