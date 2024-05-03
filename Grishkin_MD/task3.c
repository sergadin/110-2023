#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int compare(const void* a, const void* b);
void insertionSort(int n, int arr[]);
void countingSort(int arr[], int length);
int isSorted(int arr[], int length);
void generateRandomArray(int arr[], int length);

int compare(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

void insertionSort(int length, int arr[])
{
    int sort_value, j;

	for (int i = 1; i < length; i++){
		sort_value = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > sort_value){
			arr[j + 1] = arr[j];
			j -= 1;
		}

		arr[j + 1] = sort_value;
	}
}

void countingSort(int arr[], int length)
{
    int min = arr[0];
    int max = arr[0];

    for (int i = 1; i < length; i++){
        if (arr[i] < min){
            min = arr[i];
        }
        if (arr[i] > max){
            max = arr[i];
        }
    }

    int countSize = max - min + 1;
    int* count = (int*)malloc(countSize * sizeof(int));

    for (int i = 0; i < countSize; i++){
        count[i] = 0;
    }

    for (int i = 0; i < length; i++){
        count[arr[i] - min]++;
    }

    int temp = 0;
    for (int i = 0; i < countSize; i++){
        for (int j = 0; j < count[i]; j++){
            arr[temp++] = i + min;
        }
    }

    free(count);
}

int isSorted(int arr[], int length)
{
    for (int i = 1; i < length; i++) {
        if (arr[i] < arr[i - 1])
            return 0;
    }
    return 1;
}

void generateRandomArray(int arr[], int length)
{
    srand(time(NULL));
    for (int i = 0; i < length; i++)
        arr[i] = rand()%100;
}

int main(void)
{
    int length;
    int repetitions;
    double timeTaken;
    clock_t startTime;
    clock_t endTime;
    int* arr;

    printf("Enter the number of elements: ");
    if ((scanf ("%d", &length) != 1) || (length < 1)) {
		printf ("nekorrektnaya dlina massiva\n");
        return -1;
    }
    printf("enter the number of repetitions: ");
    if((scanf("%d", &repetitions)!= 1)|| (repetitions < 0)){
        printf("not korr number of repetitions");
        return -1;
    }

    for (int i = 0; i < repetitions; i++) {
        arr = (int*)malloc(length * sizeof(int));

        generateRandomArray(arr, length);

        if (length <= 100000){
            startTime = clock();
            insertionSort(length, arr);
            endTime = clock();

            timeTaken = (double)(endTime - startTime) / CLOCKS_PER_SEC;
            printf("Insertion Sort: N = %d,  Time taken:  %f seconds\n", length, timeTaken);


            if (!isSorted(arr, length)){
                printf("Array not sorted by Insertion Sort\n");
                return -1;
            }
        }

        startTime = clock();
        countingSort(arr, length);
        endTime = clock();
        timeTaken = (double)(endTime - startTime) / CLOCKS_PER_SEC;
        printf("Counting Sort: N = %d,  Time taken:  %f seconds\n", length, timeTaken);

        if (!isSorted(arr, length)){
            printf("Array not sorted by Counting Sort\n");
            return -1;
        }

        startTime = clock();
        qsort(arr, length, sizeof(int), compare);
        endTime = clock();
        timeTaken = (double)(endTime - startTime) / CLOCKS_PER_SEC;
        printf("qsort: N = %d,  Time taken:  %f seconds\n", length, timeTaken);

        if (!isSorted(arr, length)){
            printf("Array not sorted by qsort\n");
            return -1;
        }
        length *= 2;
    }

    return 0;
}
