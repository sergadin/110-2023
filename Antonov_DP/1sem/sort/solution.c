#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comp(const void *i, const void *j);	//сравнение двух целых
int pyramid_sort(double *arr, int len);      //сортирует пирамидальным методом
int bubble_sort(double *arr, int len);      //сортирует пузырьковым методом
int sorted_arr(double *arr, int len);	//проверяет отсортирован массив или нет
int make_trian(double *arr, int pl);	//создаёт треугольник, где каждая точка основания меньше вершины

int make_trian(double *arr, int pl)
{
	double save;
	if ((arr[pl] < arr[(2 * pl) + 1]) && (arr[(2 * pl) + 2] < arr[(2 * pl) + 1]))
	{
		save = arr[pl];
		arr[pl] = arr[(2 * pl) + 1];
		arr[(2 * pl) + 1] = save;
		return (2 * pl) + 1;
	}
	save = arr[pl];
       	arr[pl] = arr[(2 * pl) + 2];
       	arr[(2 * pl) + 2] = save;
	return (2 * pl) + 2;
}

int comp(const void *i, const void *j) { return *(double *)i - *(double *)j; }

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
        int i, j;
        double save;
	for (i = 0; i < len; i++)
	{
		j = (2 * i) + 1;
		if (((j + 1) < len) && ((arr[i] < arr[j + 1]) || (arr[i] < arr[j])))
		{
			make_trian(arr, i);
			i = -1;
		}
		else if (((j + 1) == len) && (arr[i] < arr[j]))
		{
			save = arr[i];
			arr[i] = arr[j];
			arr[j] = save;
			i = -1;
		}
	}
	for (i = len - 1; i > -1; i--)
	{
		save = arr[0];
		arr[0] = arr[i];
		arr[i] = save;
		j = 0;
		while((((2 * j) + 2) < i) && ((arr[j] < arr[(2 * j) + 1]) || (arr[j] < arr[(2 * j) + 2])))
		{
			if ((((2 * j) + 1) < i) && ((arr[j] < arr[(2 * j) + 1]) || (arr[j] < arr[(2 *j) + 2])))
       		      	{
        	              	j = make_trian(arr, j);
         	    	}
		}
		if ((((2 * j) + 2) == i) && (arr[j] < arr[(2 * j) + 1]))
		{
			save = arr[j];
			arr[j] = arr[(2 * j) + 1];
			arr[(2 * j) + 1] = save;
		}
	}
	return 0;
}


int main (void)
{
	double *arr1, *arr2, *arr3;
	double seconds;
	clock_t t1, t2;
	int len, i, p;
	printf ("введите длинну массива: ");
        scanf ("%d", &len);
	printf("\n");
	for (p = 0; p < 4; p++)
	{
		arr1 = (double *)malloc(len * sizeof(double));
		arr2 = (double *)malloc(len * sizeof(double));
		arr3 = (double *)malloc(len * sizeof(double));
		for (i = 0; i < len; i++)
		{
			arr1[i] = rand();
			arr2[i] = arr1[i];
			arr3[i] = arr1[i];
		}
		printf("%d \n", len);
		t1 = clock();
		bubble_sort(arr1, len);
		t2 = clock();
		seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
		if (sorted_arr(arr1, len) == 1) 
		{ 
			printf("bubble sort time: %lf \n", seconds);
       		}
		t1 = clock();
        	pyramid_sort(arr2, len);
        	t2 = clock();
        	seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
		if (sorted_arr(arr2, len) == 1) 
		{ 
			printf("pyramid sort time: %lf \n", seconds); 
		}
		t1 = clock();
        	qsort(arr3, len, sizeof (double), comp);
        	t2 = clock();
        	seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
		if (sorted_arr(arr3, len) == 1) 
		{ 
			printf("qsort time: %lf \n \n", seconds); 
		}
		free(arr1);
		free(arr2);
		free(arr3);
		len = len * 2;
	}
        return 0;
}
