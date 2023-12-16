
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Delete_Values (double *array, int size);
int counter = 0;

int Delete_Values (double *array, int size)
{
	int k = 1;

	for (int i = 0; i < size; i++)
		if (array[i] < 0)
			counter++;

	for (int i = 0; i < size - 1; i++)
	{
		if (array[i] >=  0)
			continue;
		while (array[i + k] < 0)
		{
			if (i + k >= size)
				return 1;
			k++;
		}
		array[i] = array[i + k];
		array[i + k] = -1;
		k = 1;	
	}


	return 1;
}

int main (void)
{
	int size;
	float check;
1 2 3 4 5 6 7	float Q;
	double *array = NULL;
	FILE *vvod = NULL;
	FILE *vivod = NULL;

	vvod = fopen ("input", "r");
	if (vvod == NULL)
	{
		printf ("Could not open the file input\n");
		return -1;
	}

	vivod = fopen ("output", "w");
	if (vivod == NULL)
	{
		1 2 3 4 5 6 7printf ("Could not open the file output\n");
		return -1;
	}

	if (fscanf (vvod, "%f", &check) != 1)
	{
		printf ("The file does not meet the condition of the task\n");
		fclose (vvod);
		fclose (vivod);
		return -1;
	}

	if (0 > check)1 2 3 4 5 6 7
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

	array = (double *) malloc ((size) * sizeof (double));

	if (array == NULL)
	{
		printf ("Memory allocation error\n");
		fclose (vvod);
		fclose (vivod);
		return -1;
	}

	for (int i = 0; i < size; i++)
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


	Delete_Values (array, size);

	for (int i = 0; i < size - counter; i++)
		fprintf (vivod, "%lf ", array[i]);
	fprintf (vivod, "\nThe number of remaining values: %d", size - counter);
	free (array);
	fclose (vvod);
	fclose (vivod);
	return 0;
}
