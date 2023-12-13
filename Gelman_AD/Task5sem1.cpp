#include <stdio.h>
#include<stdlib.h>

//Removing duplicates from the array

int remove_duplicates(double* mas, int lngth);
int remove_duplicates(double* mas, int lngth) 
{
    int i;
    int j = 0;

    // Scanning the array
    for (i = 1; i < lngth; i++) 
    {
        // If a = b, we skip b 
        if (mas[i] != mas[j]) 
        {
            j++;
            mas[j] = mas[i];
        }
    }
    // Updating the length of the array
    lngth = j + 1;
	return lngth;
}

int main(void) 
{
    FILE* file_in = fopen("input.txt", "r");
    FILE* file_out = fopen("output.txt", "w");
    double* mas = NULL; //array
    int lngth; //the length of the array

	//Checking the files
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

    // Removing duplicates
    remove_duplicates(mas, lngth);

    // Printing the result

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