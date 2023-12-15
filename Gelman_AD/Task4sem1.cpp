#include<stdio.h>
#include<stdlib.h>

//I read elements from the file and figure out the lengh of the array

void shiftrightk(double* mas, int lngth, int K);
//shiftrightK shifts the array "mas" in a cycle, every element shifts to the right

void reversemas(double* mas, int left, int right);
// reversemas reverses the array
void reversemas(double* mas, int left, int right)
{
	for (left = left; left < right; left++)
	{
		right = mas[left];
		mas[left] = mas[right - left - 1];
		mas[right - left - 1] = right;
	}
}

void shiftrightk(double* mas, int lngth, int K)
{
	int left;
	int right;

	if (lngth == 0)
	{
		printf("No array, lngth = 0\n");
		return;
	}

	//no elements to shift (only 1 element)
	if (lngth == 1)
	{
		return;
	}

	//Reverse all array
	left = 0;
	right = lngth;
	reversemas(mas, left, right);

	//Reverse the first part of the array (before the Kth element)
	left = 0;
	right = K;
	reversemas(mas, left, right);

	//Reverse the second part of the Array (after the Kth element)
	left = K;
	right = lngth;
	reversemas(mas, left, right);
}

int main(void)
{
	int lngth; //the length
	int K; //We will shift the array K times to the right
	FILE* file_in = fopen("input.txt", "r");
	FILE* file_out = fopen("output.txt", "w");
	double* mas = NULL;

	if (file_in == NULL)
	{
		printf("Unable to open the file input.txt\n");
		return -1;
	}

	if (file_out == NULL)
	{
		printf("Unable to open the file output.txt\n");
		fclose(file_in);
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

	//Reading K, entered from the keyboard

	printf("Enter the value of shifting the array\n");

	scanf("%d", &K);

	K %= lngth;

	//Shifting the array K times to the right

	shiftrightk(mas, lngth, K);

	for (int i = 0; i < lngth; i++)
	{
		fprintf(file_out, "%lf ", mas[i]);
	}

	if (lngth != 0)
	{
		printf("The result is printed\n");
	}

	free(mas);
	fclose(file_in);
	fclose(file_out);

	return 0;
}