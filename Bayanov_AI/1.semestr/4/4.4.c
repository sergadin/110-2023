
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Senior_position (int N);

int Senior_position (int N)
{
    int counter = 0;
	N = abs (N);
	while(N != 0)
	{ 
	    N >>= 1;
		counter++;
	}
	return counter;
}

	int
main (void)
{
	FILE *output;
	int N;
	printf ("Enter N: ");
	scanf ("%d", &N);
	output = fopen ("output.txt", "w");
	fprintf (output, "The position of the highest bit: %d\n", Senior_position (N));
	fclose (output);
	return 0;
}
