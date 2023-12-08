#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int LngthSet(int* mas, int lngth);
int LngthSet(int* mas, int lngth)
{

	int finlngth = lngth;
	int dublicate;
	int i;

	for (int firstel = 0; firstel < finlngth - 1; firstel++)
	{

		i = firstel;

		while (mas[i + 1] == mas[i])
		{
			i++;
		}

		dublicate = i - firstel; //removing dublicates
		finlngth -= dublicate;

		ShiftByK(mas, firstel + dublicate + 1, firstel + 1); //Shifting the array after deliting dublicates

		ShiftByK(mas, lngth, dublicate);

	}

	return finlngth;
}

void ShiftByK(int* mas, int lngth, int dublicate); // shifting the array K = dublicate times to the right
void ShiftByK(int* mas, int lngth, int dublicate)
{
	int shiftIndex = (lngth - dublicate) % lngth;
	int temp; //temporary index

	for (i = 0; i < lngth; i++)
	{
		temp = mas[i];

		// Count the index after shifting the array
		int newIndex = (i + shiftIndex) % lngth;
		mas[i] = mas[newIndex];
		mas[newIndex] = temp;
	}
}

int main(void)
{
	FILE* file_in = fopen("input.txt", "r");
	FILE* file_out = fopen("output.txt", "w");		
	char fi[30];		
	char fo[30];		
	int code;		
	int* mas = NULL;	
	int lngth;		

	//Checking the files 

	if (file_in == NULL)
	{
		printf("Unable to open the file input.txt\n", file_in);
		fclose(file_in);
		return -1;
	}

	if (file_out == NULL)
	{
		printf("Unable to open the file output.txt\n");
		fclose(file_out);
		return -1;
	}

	if (fscanf(file_in, "%d", &lngth) != 1)
	{
		printf("Unable to read the file\n");
		fclose(file_in);
		fclose(file_out);
		return -1;
	}

	mas = (double*)malloc((lngth) * sizeof(double));

	if (mas == NULL)
	{
		printf("Memory error\n");
		fclose(file_in);
		fclose(file_out);
		return -1;
	}

	for (int i = 0; i < lngth; i++)
	{
		if (fscanf(file_in, "%lf", &mas[i]) != 1)
		{
			printf("Problems with array\n");
			free(mas);
			fclose(file_in);
			fclose(file_out);
			return -1;
		}
	}

	//Array function
	code = LngthSet(mas, lngth); 

	if (code < 0)
	{
		return code;
	}

	printf("The result is uploaded to the file '%s'\n", file_out);

	fprintf(file_out, "Number of elements in the array without repetitions %d\nThe array itself without repetitions: ", code);

	//Final result in the file output.txt

	for (int i = 0; i < code; i++)
	{
		fprintf(file_out, "%d ", mas[i]);
	}

	fclose(file_out);
	free(mas);

	return 0;
}