

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int Number_Search (FILE * input, float X);

int Number_Search (FILE * input, float X)
{
	float element;
	int answer = -1;
	int scan;
	if (fscanf (input, "%f", &element) ==  0)
	{
		return 0;
	}
         if(element - X < 0.00001 && element >= X)
                        answer = 1;

         if (X - element < 0.00001 && element <= X)
                        answer = 1;

	while (!feof (input))
	{
		scan = fscanf (input, "%f", &element);

		if (scan == 0)
		{
			return 0;
		}
		if (element - X < 0.00001 && element >= X)
			answer = 1;

		if (X - element < 0.00001 && element <= X)
			answer = 1;
	}

	return answer;
}


int main (void)
{
	FILE *input = NULL;
	char name[1000];
	float X;
	int Function;
	printf ("Enter the file name: ");
	scanf ("%s", name);
	printf ("Enter the number X: ");
	scanf ("%f", &X);

	input = fopen (name, "r");
	if (input == NULL)
	{
		printf ("Could not open the file\n");
		return -1;
	}

	Function = Number_Search (input, X);

	if (Function == 0)
		printf ("The file does not meet the condition of the task\n");
	if (Function == 1)
		printf ("Yes\n");
	if (Function == -1)
		printf ("No\n");

	fclose (input);
	return 0;
}
