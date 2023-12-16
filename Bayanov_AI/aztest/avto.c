#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
int max;

int Dominirovanie(double *array_A, double *array_B, int size_A, int size_B);

int Dominirovanie(double *array_A, double *array_B, int size_A, int size_B)
{
	int sum = 0;
	int counter = 0;
	max = array_A[0];
	for(int i=0; i < size_A; i++)
	{
		if(array_A[i] > max)
			max = array_A[i];
	}
	max += 2;
	for(int i = 0; i < size_A; i++)
	{      
		if(i < size_B)
			sum += array_B[i];
		if(array_A[i] > sum)
		{
			counter++;
			continue;
		}
		array_A[i] = max;
	}
	return counter;
}


int main (void)
{
	FILE * inA = NULL;
	FILE * inB = NULL;
	FILE *output = NULL;
	double *array_A = NULL;
	double *array_B = NULL;
	int size_A;
	int size_B;
	float check = 0;

	inA = fopen("inA.txt", "r");
	if(inA == NULL)
		return -1;
	if(fscanf(inA, "%f", &check) != 1)
	{
		fclose(inA);
		return -1;
	}
	size_A = check;

	if(check <= 0)
	{
		fclose(inA);
		return -1;
	}
	if(size_A < check)
	{
		fclose(inA);
		return -1;
	}
	array_A = (double *) malloc ((size_A) * sizeof(int));
	for(int i = 0; i < size_A; i++)
		if(fscanf(inA, "%lf", &array_A[i]) != 1)
		{
			fclose(inA);
			return -1;
		}
	fclose(inA);

	inB = fopen("inB.txt", "r");
	if(inB == NULL)
		return -1;
	if(fscanf(inB, "%f", &check) != 1)
	{
		fclose(inB);
		return -1;
	}
	size_B = check;

	if(check <= 0)
	{
		fclose(inB);
		return -1;
	}
	if(size_B < check)
	{
		fclose(inB);
		return -1;
	}
	array_B =  (double *) malloc ((size_B) * sizeof(int));
	for(int i = 0; i < size_B; i++)
		if(fscanf(inB, "%lf", &array_B[i]) != 1)
		{
			fclose(inB);
			return -1;
		}
	fclose(inB);

	output = fopen("output.txt", "w");
	if(output == NULL)
		return -1;
	fprintf(output, "%d ", Dominirovanie(array_A, array_B, size_A, size_B));
	for(int i =0; i < size_A; i++)
	{
		if(array_A[i] > max-1)
			continue;
		fprintf(output, "%lf ", array_A[i]);   
	}

	fclose(output);
	free(array_A);
	free(array_B);

	return 0;

}   
