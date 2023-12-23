#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comp(const int *i, const int *j);	//сравнение двух целых
int pyramid_sort(double *arr, int len);      //сортирует пирамидальным методом
int bubble_sort(double *arr, int len);      //сортирует пузырьковым методом
int sorted_arr(double *arr, int len);

int comp(const int *i, const int *j) { return *i - *j; }

int bubble_sort (double *arr, int len)
{
	int i, j;
	double save;
	for (i = 0; i < len; i++)
	{
		for (j = i; j < len; j++)
		{
			if (arr[i] > arr[j])
			{
				save = arr[i];
				arr[i] = arr[j];
				arr[j] = save;
			}
		}
	}
	return 0;
}

int pyramid_sort (double *arr, int len)
{
        int i, j, p = 1;
        double save;
	while (p < len)
	{
		for (i = 0; i < ((int) len / 2) - 1; i++)
		{
			j = (2 * i) + 1;
			if ((arr[i] < arr[j]) && (arr[j + 1] < arr[j]))
			{
				save = arr[i];
				arr[i] = arr[j];
				arr[j] = save;
				}
			else if ((arr[i] < arr[j + 1]))
			{
				save = arr[i];
				arr[i] = arr[j + 1];
				arr[j + 1] = save;
			}
		}
		p = p * 2;
	}
	return 0;
}


int main (void)
{
	double *arr1, *arr2, *arr3;
	double seconds;
	clock_t t1, t2;
	int len, i;
	printf ("введите длинну массива: ");
        scanf ("%d \n", &len);
	arr1 = (double *)malloc(len * sizeof(double));
	arr2 = (double *)malloc(len * sizeof(double));
	arr3 = (double *)malloc(len * sizeof(double));
	for (i = 0; i < len; i++)
	{
		arr1[i] = rand();
		arr2[i] = arr1[i];
		arr3[i] = arr1[i];
	}
	t1 = clock();
	bubble_sort(arr1, len);
	t2 = clock();
	seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
	if (sorted_arr(arr1, len) == 1) { printf("bubble sort time: %lf \n", seconds); }
	t1 = clock();
        pyramid_sort(arr2, len);
        t2 = clock();
        seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
	if (sorted_arr(arr2, len) == 1) { printf("pyramid sort time: %lf \n", seconds); }
	t1 = clock();
        qsort(arr3, len, sizeof (double), (double(*) (const void *, const void *)) comp);
        t2 = clock();
        seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
	if (sorted_arr(arr3, len) == 1) { printf("qsort time: %lf \n", seconds); }
	for (i = 0; i < len; i++)
	{
		printf("%lf \n", arr3[i]);
	}
	free(arr1);
	free(arr2);
	free(arr3);
        return 0;
}
