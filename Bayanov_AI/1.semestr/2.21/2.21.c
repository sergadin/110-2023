
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Even_numbers_at_the_beginning (double *array, int size);


int Even_numbers_at_the_beginning (double *array, int size)
{
  float save;
  for(int i = 1; i < size/2+1; i++)
   {
      for(int j = 0; j < i; j++)
      {
         save = array[2*i-j-1];
         array[2*i-j-1] = array[2*i-j];
         array[2*i-j] = save;
      }
   }
       
   
  return 1;
}

int main (void)
{
  int size;
  float check;
  float Q;
  double *array = NULL;
  FILE *vvod = NULL;
  FILE *vivod = NULL;
  
  vvod = fopen ("input", "r");
  if(vvod == NULL)
    {
      printf ("Could not open the file input\n");
      return -1;
    }

  vivod = fopen ("output", "w");
  if(vivod == NULL)
    {
      printf ("Could not open the file output\n");
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

  array = (double *) malloc ((size+1) * sizeof (double));

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


  Even_numbers_at_the_beginning (array, size);

  for (int i = 1; i < size + 1; i++)
    fprintf (vivod, "%lf ", array[i]);
    
  free (array);
  fclose (vvod);
  fclose (vivod);
  return 0;
}

