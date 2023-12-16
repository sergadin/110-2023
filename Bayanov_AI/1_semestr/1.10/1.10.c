
#include <stdio.h>
#include <math.h>
int The_number_of_different_numbers_in_the_sequence (FILE * input);

int The_number_of_different_numbers_in_the_sequence (FILE * input)
{
	int current;
	int previous;
	int counter = 0;
	if (fscanf (input, "%d", &current) != 1)
		return -1;
	counter++;
	previous = current;
	while (!feof (input))
	{
		if (fscanf (input, "%d", &current) == 0)
			return -1;
		if (previous > current)
		{
			return -1;
		}
		if (previous < current)
		{
			counter++;
			previous = current;
		}
	}
	fclose (input);
	return counter;
}

int main (void)
{
	FILE *input;
	char file_name[1000];
	int answer;
	printf ("Enter the file name: ");
	scanf ("%s", file_name);
	input = fopen (file_name, "r");
	if (input == NULL)
	{
		printf ("Could not open the file\n");
		return -1;
	}

	answer = The_number_of_different_numbers_in_the_sequence (input);
	if (answer == -1)
		printf ("The file does not meet the condition of the task\n");
	if (answer > 0)
		printf ("%d\n", answer);
	return 0;
}
