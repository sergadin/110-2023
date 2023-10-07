#include <stdio.h>

int test_file (FILE *input);
int compute_midar (FILE *input);

int compute_midar (FILE *input)
{
	int quan = 0;
	float curr = 0, summ = 0, answ = 0;
	if (fscanf (input, "%f", & summ) != 1){
		return -1;
	}
	curr = summ;
	quan = 1;
	while (fscanf (input, "%f", & curr) == 1 && (int) curr != 0)
	{
		summ += curr;
		quan += 1;
	}
	answ = summ/quan;
	return answ;
}

int main (void)
{
	float answ = 0;
	FILE *input, *output;
	input = fopen ("input.txt", "r");
	output = fopen ("output.txt", "r");
	if (test_file (input) == -1){
		return -1;
	}
	if (test_file (output) == -1){
		return -1;
	}
	answ = compute_midar (input);
	fprintf (output, "answ = %f \n", answ);
	fclose (input);
	fclose (output);
	return 0;
}
