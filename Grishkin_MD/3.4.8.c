#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int compare(const void* a, const void* b);
void insertionSort(int arr[], int length);
void countingSort(int arr[], int length);
int isSorted(int arr[], int length);
void generateRandomArray(int arr[], int length);

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}
void insertionSort(int arr[], int length) {
    int key, j;
    for (int i = 1; i < length; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void countingSort(int arr[], int length) {
    int min = arr[0];
    int max = arr[0];
    int temp = 0;
    for (int i = 1; i < length; i++){
        if (arr[i] < min){
            min = arr[i];
        }
        if (arr[i] > max){
            max = arr[i];
        }
    }

    int* count = (int*)malloc((max - min + 1) * sizeof(int));
    for (int i = 0; i < max - min + 1; i++){
        count[i] = 0;
    }

    for (int i = 0; i < length; i++){
        count[arr[i] - min]++;
    }

    int index = 0;
    for (int i = 0; i < max - min + 1; i++){
        for (int j = 0; j < count[i]; j++){
            arr[temp++] = i + min;
        }
    }
}
int isSorted(int arr[], int length) {
    for (int i = 1; i < length; i++) {
        if (arr[i] < arr[i - 1])
            return 0;
    }
    return 1;
}

void generateRandomArray(int arr[], int length) {
    srand(time(NULL));
    for (int i = 0; i < length; i++)
        arr[i] = rand();
}

int main(void) {
    int length;
    int repetitions = 3;
    double timeTaken;
    clock_t startTime;
    clock_t endTime;
    int* arr;

    printf("Enter the number of elements: ");
    if ((scanf ("%d", &length) != 1) || (length < 1)) {
		printf ("nekorrektnaya dlina massiva\n");
        return -1;
    }

    for (int i = 0; i < repetitions; i++) {
        arr = (int*)malloc(length * sizeof(int));

        generateRandomArray(arr, length);

        startTime = clock();
        insertionSort(arr, length);
        endTime = clock();
        timeTaken = (double)(endTime - startTime) / CLOCKS_PER_SEC;
        printf("Insertion Sort: N = %d, Time taken: %f seconds\n", length, timeTaken);

        if (!isSorted(arr, length))
            printf("Array not sorted by Insertion Sort\n");

        startTime = clock();
        countingSort(arr, length);
        endTime = clock();
        timeTaken = (double)(endTime - startTime) / CLOCKS_PER_SEC;
        printf("Counting Sort: N = %d, Time taken: %f seconds\n", length, timeTaken);

        if (!isSorted(arr, length))
            printf("Array not sorted by Counting Sort\n");

        startTime = clock();
        qsort(arr, length, sizeof(int), compare);
        endTime = clock();
        timeTaken = (double)(endTime - startTime) / CLOCKS_PER_SEC;
        printf("qsort: N = %d, Time taken: %f seconds\n", length, timeTaken);

        if (!isSorted(arr, length)){
            printf("Array not sorted by qsort\n");
        }
        length *= 2;
    }

    return 0;
}