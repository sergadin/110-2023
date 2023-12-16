#include <stdio.h>
#include <stdlib.h>

int domin_A(double *arr1, double *arr2, int len1, int len2);

int domin_A(double *arr1, double *arr2, int len1, int len2)
{
	int i,  len = 0;
	double summ = 0;
	for (i = 0; (i < len1) && (i < len2); i++)
	{
		summ += arr2[i];
		if (arr1[i] > summ)
		{
			arr1[len] = arr1[i];
			len++;
		}
	}
	for (; i < len1; i++)
	{
		if (arr1[i] >summ)
		{
			arr1[len] = arr1[i];
			len++;
		}
	}
	return len;
}


int main (void)
{
	int i = 0, len1, len2, len;
	double *arr1, *arr2;
	FILE *input1, *input2, *output;
	input1 = fopen("inA.txt", "r");
	input2 = fopen("inB.txt", "r");
	output = fopen("output.txt", "w");
	if ((input1 == NULL) || (input2 == NULL) || (output == NULL)) { return -1; }
	if ((feof(input1) != 0) || (feof(input2) != 0)) { return -1; }
	if (fscanf(input1, "%d", &len1) != 1) { return -1; }
	arr1 = (double *)malloc(len1 * sizeof(double));
	for (i = 0; i < len1; i++)
	{
		if (feof(input1) != 0) { return -1; }
		if (fscanf(input1, "%lf", &arr1[i]) != 1) { return -1; }
	}
	if (fscanf(input2, "%d", &len2) != 1) { return -1; }
	arr2 = (double *)malloc(len2 * sizeof(double));
	for (i = 0; i < len2; i++)
        {
                if (feof(input2) != 0) { return -1; }
                if (fscanf(input2, "%lf", &arr2[i]) != 1) { return -1; }
        }
	len = domin_A(arr1, arr2, len1, len2);
	fprintf(output, "%d \n", len);
	for (i = 0; i < len; i++)
	{
		fprintf(output, "%lf \n", arr1[i]);
	}
	free (arr1);
	free (arr2);
	fclose (input1);
	fclose (input2);
	fclose (output);
	return 0;
}
