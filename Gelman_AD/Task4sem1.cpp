#include<stdio.h>
#include<stdlib.h>

//I read elements from the file and figure out the lengh of the array

void shiftrightk(double* mas, int lngth);
//shiftrightK shifts the array "mas" in a cycle, every element shifts to the right

void shiftrightk(double* mas, int lngth)
{
	double finel;

	if (lngth == 0)
	{
		printf("No array, lngth = 0\n");
		return;
	}

	if (lngth == 1)
	{     //no elements to shift (only 1 element)
		return;
	}


	for (int i = 0; i < K; i++)
	{
		finel = mas[lngth - 1];    //save the last element of the array

		for (int i = lngth - 1; i > 0; i--)
		{		//shift elements to the right
			mas[i] = mas[i - 1];
		}

		mas[0] = finel;
	}

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

	mas = (double*)malloc((lngh) * sizeof(double));

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

	scanf("%d",  & K);

	if (K > lngth)
	{
		printf("Enter the fewer value of K\n");
	}

	//Shifting the array K times to the right

	shiftrightk(mas, lngth);

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