#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define SORTED 1
#define UNSORTED -1

void random_mas(int lngth, int* mas1, int* mas2, int* mas3); //Creating random array
void sift_sort(int* mas, int lngth); //Sift sorting
void quick_sort(int* mas, int lngth); //Quick sorting
int test_sort(int* mas, int lngth); //Testing wether the array is sorted
int comp(const int* a, const int* b); //Helping function for quick_sort

//Creating random array
void random_mas(int lngth, int* mas1, int* mas2, int* mas3) 
{
	int r;

	for (int i = 0; i < lngth; i++) 
	{
		r = rand() % 1000;		 //rand()% 1000 random integer in range [0; 999]
		mas1[i] = r;
		mas2[i] = r;
		mas3[i] = r;
	}
}

//Sift sorting
void sift_sort(int* mas, int lngth) 
{
	int i;
	//first == first unsorted element
	//last == last sorted element

	for (int first = 1; first < lngth; first++) 
	{
		for (int last = first; (last > 0) && (mas[last] < mas[last - 1]); last--) 
		{
			i = mas[last];
			mas[last] = mas[last - 1];
			mas[last - 1] = i;
		}
	}
}

//Quick sorting
void quick_sort(int* mas, int lngth) 
{
	int i = 0;
	int j = lngth - 1;

	// Central element of the array
	int mid = mas[lngth / 2];

	// Split the array
	do //while (i <= j)
	{
		// Run through all elements and find elements that must go to the other side of the array
		// On the left side of the array we skip those elements that are less than the mid one
		while (mas[i] < mid) 
		{
			i++;
		}
		// On the right side of the array we skip those elements that are bigger than the mid one
		while (mas[j] > mid) 
		{
			j--;
		}

		// Swap eleemnts
		if (i <= j) 
		{
			int tmp = mas[i];
			mas[i] = mas[j];
			mas[j] = tmp;

			i++;
			j--;
		}
	} while (i < j);

	// Recursive function if there are unsorted elements
	if (j > 0) 
	{
		// Left side
		quick_sort(mas, j - 1);
	}
	if (i < lngth) 
	{
		// Right side
		quick_sort(&mas[i], lngth - i);
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

//Helping function for quick_sort
int comp(const int* a, const int* b) 
{
	return *a - *b;
}


int main(void) 
{
	int lngth;
	int test_1, test_2;
	clock_t start_1, start_2, start_3, end_1, end_2, end_3; //Time of the sorting process
	double time_1, time_2, time_3; //Result time of the sorting process
	int* mas1 = NULL; // An array for sift sorting
	int* mas2 = NULL; // An array for quick sorting
	int* mas3 = NULL; // An array for sorting with the qsort function

	printf("Enter the length of the array: lngth = \n");

	if ((scanf("%d", &lngth) != 1) || (lngth < 1))
	{
		printf("Incorrect value of the length\n");
		return -1;
	}

	mas1 = (int*)malloc((lngth * pow(2, 4)) * sizeof(int));
	mas2 = (int*)malloc((lngth * pow(2, 4)) * sizeof(int));
	mas3 = (int*)malloc((lngth * pow(2, 4)) * sizeof(int));

	if (mas1 == NULL) 
	{
		printf("Memory error mas1\n");
		return -1;
	}
	if (mas2 == NULL) 
	{
		printf("Memory error mas2\n");
		return -1;
	}
	if (mas3 == NULL) 
	{
		printf("Memory error mas3\n");
		return -1;
	}

	//Scanning lengths of random arrays
	for (int i = 0; i < 5; i++) 
	{	
		//Creating random array
		random_mas(lngth, mas1, mas2, mas3);

		//Sift sorting
		start_1 = clock();
		sift_sort(mas1, lngth);
		end_1 = clock();

		//Quick sorting
		start_2 = clock();
		quick_sort(mas2, lngth);
		end_2 = clock();

		//Sorting with the qsort function
		start_3 = clock();
		qsort(mas3, lngth, sizeof(int), (int(*) (const void*, const void*)) comp);
		end_3 = clock();

		//The resulting time == time (double)
		time_1 = (double)(end_1 - start_1) / CLOCKS_PER_SEC;
		time_2 = (double)(end_2 - start_2) / CLOCKS_PER_SEC;
		time_3 = (double)(end_3 - start_3) / CLOCKS_PER_SEC;

		//Testing the oderliness of the array
		test_1 = test_sort(mas1, lngth);
		test_2 = test_sort(mas2, lngth);

		//Printing the result
		if (test_1 == UNSORTED) 
		{
			//The sift sorting is incorrect with this value of the length
			printf("The sift sorting is incorrect with this value of the length: %d \n", lngth);
		}
		else //(test_1 == SORTED)
		{
			printf("//The time of sift sorting: %lf with length: %d \n", time_1, lngth);
		}

		if (test_2 == UNSORTED) 
		{
			//The quick sorting is incorrect with this value of the length
			printf("The quick sorting is incorrect with this value of the length: %d \n", lngth);
		}
		else //(test_2 == SORTED)
		{
			printf("The time of quick sorting: %lf with length: %d \n", time_2, lngth);
		}

		printf("The time of sorting with qsort function: %lf\n", time_3);
		printf("\n");

		lngth = lngth * 2;
	}

	free(mas1);
	free(mas2);
	free(mas3);

	return 0;
}