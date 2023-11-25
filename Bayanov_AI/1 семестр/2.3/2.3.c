
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Cyclic_shift (double *array, int size);


int
Cyclic_shift (double *array, int size)
{
  double t1 = array[1];
  double t2;
  array[1] = array[size];
  if (size > 1)
    for (int i = 2; i < size + 1; i++)
      {
	t2 = array[i];
	array[i] = t1;
	t1 = t2;
      }
  return 1;
}

int
main (void)
{
  int size;
  float check;
  float Q;
  double *array = NULL;
  FILE *vvod = fopen ("input", "r");
  FILE *vivod = fopen ("output", "w");

  if (vvod == NULL)
    {
      printf ("Could not open the file input\n");
      return -1;
    }

  if (vivod == NULL)
    {
      printf ("Could not open the file output\n");
      fclose (vivod);
      return -1;
    }

  if (fscanf (vvod, "%f", &check) != 1)
    {
      printf ("The file does not meet the condition of the task\n");
      fclose (vvod);
      fclose (vivod);
      return -1;
    }

  if (0 > check)
    {
      printf ("The length of the array is incorrect \n");
      fclose (vvod);
      fclose (vivod);
      return -1;
    }

  size = check;

  if (size < check)
    {
      printf ("The length of the array is incorrect \n");
      fclose (vvod);
      fclose (vivod);
      return -1;
    }

  array = (double *) malloc ((size + 1) * sizeof (double));

  if (array == NULL)
    {
      printf ("Memory allocation error\n");
      fclose (vvod);
      fclose (vivod);
      return -1;
    }

  for (int i = 1; i < size + 1; i++)
    {
      if (fscanf (vvod, "%lf", &array[i]) != 1)
	{
	  printf ("The file does not meet the condition of the task\n");
	  free (array);
	  fclose (vvod);
	  fclose (vivod);
	  return -1;
	}
    }

  while (!feof (vvod))
    if (fscanf (vvod, "%f", &Q) != -1)
      {
	printf ("The file does not meet the condition of the task\n");
	return -1;
      }


  Cyclic_shift (array, size);

  for (int i = 1; i < size + 1; i++)
    fprintf (vivod, "%lf ", array[i]);

  free (array);
  fclose (vvod);
  fclose (vivod);
  return 0;
}
