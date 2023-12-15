#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define SORTED 1
#define UNSORTED -1

void random_mas(int lngth, int* mas); //Creating random array
void sift_sort(int* mas1, int lngth); //Sift sort
int test_sort(int* mas, int lngth); //Testing wether the array is sorted

//Creating random array
void random_mas(int lngth, int* mas) 
{
	int r;

	for (int i = 0; i < lngth; i++) 
	{
		r = rand() % 1000;		 //rand()% 1000 random integer in range [0; 999]
		mas[i] = r;
	}
}

//Sift sort
void sift_sort(int* mas, int lngth) 
{
	int c;

	for (int i = 1; i < lngth; i++) 
	{
		for (int j = i; (j > 0) && (mas[j] < mas[j - 1]); j--) 
		{
			c = mas[j];
			mas[j] = mas[j - 1];
			mas[j - 1] = c;
		}
	}
}

//Testing the oderliness of the array
int test_sort(int* mas, int lngth) 
{	
	int k = SORTED;

	//The function returns SORTED if the array is sorted; 
	//The function returns UNSORTED if the array is not sorted;

	for (int i = 0; i < lngth - 1; i++) 
	{
		if (mas[i + 1] < mas[i]) 
		{
			k = UNSORTED;
		}
	}
	return k;
}

//Reading the array from the file
int main(void) 
{
	int lngth;  // The length of the array
	int test; //Testing the oderliness of the array
	clock_t start, end; //Time of the sorting process
	double time; //Result time of the sorting process
	int* mas = NULL;

	printf("Enter the length of the array: lngth = \n");

	if ((scanf("%d", &lngth) != 1) || (lngth < 1))
	{
		printf("Incorrect value of the length\n");
		return -1;
	}

	mas = (int*)malloc((lngth * pow(2, 3)) * sizeof(int));

	if (mas == NULL) 
	{
		printf("Memory error\n");
		return -1;
	}

	//Creating random array
	random_mas(lngth, mas);
	
	//Sift sort
	start = clock();
	sift_sort(mas, lngth);
	end = clock();

	//The resulting time == time (double)
	time = (double)(end - start) / CLOCKS_PER_SEC;

	//Testing the oderliness of the array
	test_sort(mas, lngth);

	//Printing the result
	if (test == UNSORTED) 
	{
		//The sift sort is incorrect with this value of the length
		printf("The sift sort is incorrect with this value of the length: %d \n", lngth);
	}
	else //(test == SORTED)
	{
		printf("The time of the sift sort: %lf with length: %d \n", time, lngth);
	}
		
	printf("\n");
	free(mas);
	return 0;
}