

#include <stdio.h>
#include <math.h>

#define ERR_FILE_EMPTY -1

int check = 0;
float Arithmetic_mean (FILE * input);

	float
Arithmetic_mean (FILE * input)
{
	int current;
	int previous1;
	int previous2;
	int counter = 0;
	float sum = 0;
	float arifm = 0;
	int scan = 0;

	if (fscanf (input, "%d", &current) == EOF)
	{
		check = ERR_FILE_EMPTY;
		return 0;
	}
	previous1 = current;
	previous2 = previous1 - 1;
	while (!feof (input))
	{
		scan = fscanf (input, "%d", &current);
		if (scan == 0)
		{
			check = -2;
			return 0;
		}
		if (scan != 1)
			continue;
		if (previous1 == current && previous2 != current)
		{
			counter++;
			sum += current;
		}
		previous2 = previous1;
		previous1 = current;
	}

	if (counter == 0)
	{
		check = -3;
		return 0;
	}

	arifm = sum / counter;

	fclose (input);

	return arifm;
}


	int
main (void)
{
	FILE *input;
	char name[1000];
	float answer;
	printf ("Enter the file name: ");
	scanf ("%s", name);

	input = fopen (name, "r");
	if (input == NULL)
	{
		printf ("Could not open the file\n");
		return -1;
	}

	answer = Arithmetic_mean (input);

	if (check == -1)
		printf ("The file is empty\n");

	if (check == -2)
		printf ("The file does not meet the condition of the task\n");

	if (check == -3)
		printf ("There are no permanent sections in the sequence\n");

	if (check == 0)
		printf ("%f\n", answer);
	return 0;
}
