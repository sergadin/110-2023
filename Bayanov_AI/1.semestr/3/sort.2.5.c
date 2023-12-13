

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Check_array (int *array, int size);

int comp (const void *i, const void *j);

int random_array (int *array_1, int *array_2, int *array_3, int size);

int Puzrk_Sort (int *array, int size);

int Slianie (int *array, int *left, int *right, int dlina_left, int dlina_right);

int Slianie_Sort (int *array, int size);

int Check_array (int *array, int size)
{
  for (int i = 0; i < size - 1; i++)
    if (array[i] > array[i + 1])
      return -1;

  return 1;
}

int
comp (const void *i, const void *j)
{
  return *(int *) i - *(int *) j;
}

int
random_array (int *array_1, int *array_2, int *array_3, int size)
{
  for (int i = 0; i < size; i++)
    {
      array_1[i] = rand ();
      array_2[i] = array_1[i];
      array_3[i] = array_1[i];
    }
  return 1;
}

int
Puzrk_Sort (int *array, int size)
{
  int temp;
  for (int j = size - 1; j >= 0; j--)
    for (int i = 0; i < j; i++)
      if (array[i] > array[i + 1])
	{
	  temp = array[i];
	  array[i] = array[i + 1];
	  array[i + 1] = temp;
	}
  return 1;
}

int
Slianie (int *array, int *left, int *right, int dlina_left, int dlina_right)
{
  int i = 0;
  int j = 0;
  int k = 0;
  while (i < dlina_left && j < dlina_right)
    if (left[i] <= right[j])
      {
	array[k] = left[i];
	k++;
	i++;
      }
    else
      {
	array[k] = right[j];
	j++;
	k++;
      }

  for (i; i < dlina_left; i++)
    {
      array[k] = left[i];
      k++;
    }

  for (j; j < dlina_right; j++)
    {
      array[k] = right[j];
      k++;
    }
  return (1);

}


int
Slianie_Sort (int *array, int size)
{
  if (size < 2)
    return 1;

  int *left;
  int *right;
  int mid = size / 2;
  left = (int *) malloc ((mid) * sizeof (int));
  right = (int *) malloc ((size - mid) * sizeof (int));

  for (int i = 0; i < mid; i++)
    left[i] = array[i];
  for (int i = mid; i < size; i++)
    right[i - mid] = array[i];

  Slianie_Sort (left, mid);
  Slianie_Sort (right, size - mid);

  Slianie (array, left, right, mid, size - mid);
  free (left);
  free (right);

  return 1;
}

int
main (void)
{
  int *array_1 = NULL;
  int *array_2 = NULL;
  int *array_3 = NULL;
  int size;

  printf ("Enter N: ");
  scanf ("%d", &size);

  int N = size;
  array_1 = (int *) malloc ((8 * N) * sizeof (int));
  array_2 = (int *) malloc ((8 * N) * sizeof (int));
  array_3 = (int *) malloc ((8 * N) * sizeof (int));
  if (array_1 == NULL)
    {
      printf ("Memory allocation error");
      return 0;
    }
  if (array_2 == NULL)
    {
      printf ("Memory allocation error");
      return 0;
    }
  if (array_3 == NULL)
    {
      printf ("Memory allocation error");
      return 0;
    }

  double time_work_1 = 0.0;
  double time_work_2 = 0.0;
  double time_work_3 = 0.0;

  clock_t begin_1;
  clock_t begin_2;
  clock_t begin_3;
  clock_t end_1;
  clock_t end_2;
  clock_t end_3;

  for (int i = 0; i < 4; i++)
    {
      printf ("N = %d\n", size);
      random_array (array_1, array_2, array_3, size);
      clock_t begin_1 = clock ();
      Puzrk_Sort (array_1, size);
      clock_t end_1 = clock ();
      time_work_1 = (double) (end_1 - begin_1) / CLOCKS_PER_SEC;
      if (Check_array (array_1, size) == -1)
	printf ("Bubble sort error\n");
      else
	printf ("Bubble sort time: %lf\n", time_work_1);

      clock_t begin_2 = clock ();
      Slianie_Sort (array_2, size);
      clock_t end_2 = clock ();
      time_work_2 = (double) (end_2 - begin_2) / CLOCKS_PER_SEC;
      if (Check_array (array_2, size) == -1)
	printf ("Merge sort error\n");
      else
	printf ("Merge sort time: %lf\n", time_work_2);

      clock_t begin_3 = clock ();
      qsort (array_3, size, sizeof (int), comp);
      clock_t end_3 = clock ();
      time_work_3 = (double) (end_3 - begin_3) / CLOCKS_PER_SEC;
      if (Check_array (array_3, size) == -1)
	printf ("qsort error\n");
      else
	printf ("qsort time: %lf\n", time_work_3);

      size = size * 2;
    }
  free (array_1);
  free (array_2);
  free (array_3);



  return 0;
}
