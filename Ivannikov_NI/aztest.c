#include <stdio.h>
#include <stdlib.h>
void readArrayFromFile(const char* filename, double** array, int*  length);
void readArrayFromFile(const char* filename, double** array, int*  length)
{
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Error opening file %s\n", filename);
		exit(1);
	}

	fscanf(file, "%d", length);
	*array = malloc(*length * sizeof(double));

	for (int i = 0; i < *length; i++)
	{
		fscanf(file, "%lf", &(*array)[i]);
	}

	fclose(file);
}

void writeArrayToFile(const char* filename, double* array, int length);
void writeArrayToFile(const char* filename, double* array, int length)
{
	FILE* file = fopen(filename, "w");
	if (file == NULL)
	{
		printf("Error openung file %s\n", filename);
		exit(1);
	}

	for(int i = 0; i < length; i++)
	{
		fprintf(file, "%.2lf", array[i]);
	}

	fclose(file);
}

void findGoodElements(double* A, int lengthA, double* B, int lengthB, double** result, int* resultLength);
void findGoodElements(double* A, int lengthA, double* B, int lengthB, double** result, int* resultLength)
{
	double sumB = 0;

	*result = malloc(lengthA *sizeof(double));
	*resultLength = 0;

	for (int i = 0; i < lengthA; i++)
	{
		sumB += B[i];

		if (A[i] > sumB)
		{
			(*result)[*resultLength] = A[i];
			(*resultLength)++;
		}
	}
}

int main(void)
{
	int lengthA, lengthB;
	double* A;
	double* B;
	double* result;
	int resultLength;

	readArrayFromFile("ina.txt", &A, &lengthA);
	readArrayFromFile("inb.txt", &B, &lengthB);

	findGoodElements(A, lengthA, B, lengthB, &result, &resultLength);

	writeArrayToFile("output.txt", result, resultLength);

	free(A);
	free(B);
	free(result);

	return 0;
}
