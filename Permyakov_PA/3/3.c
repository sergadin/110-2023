#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void slow_transposing_sort(int* array, int N);

int partition(int* array, int start, int end);

void quicksort(int* array, int start, int end);

int* ArrayGenerator(const int N);

int SortedChecker(const int* array, int N);

int* ArrayCopy(const int* array, int N);

int SortingTimeComparing(int* array, int N);

int compare(const void *a, const void *b);

int main(int argc, char** argv)
{
    int N;
    int T;
    int* array;
    if (argc != 3){
        printf("incorrect number of arguments. need two arguments - length and testing times\n");
	    return 1;
    }
    if ((!sscanf(argv[1], "%d", &N)) || (!sscanf(argv[2], "%d", &T))){
        printf("Invalid input data - need natural numbers for length and testing times");
    }
    for (int i = 0; i < T; i++){
        printf("%d\n", i + 1);
        array = ArrayGenerator(N * pow(2, i));
        SortingTimeComparing(array, N * pow(2, i));
    }
}

void slow_transposing_sort(int* array, int N)
{
    int i = 1;
    int elem;
    while (i < N){
        if (array[i - 1] > array[i]){
            elem = array[i - 1];
            array[i - 1] = array[i];
            array[i] = elem;
            i = 1;
        }
        else {
            i++;
        }
    }
}

int partition(int* array, int start, int end)
{
    int elem;
    int pivot = array[end];
    int pointer = start - 1;
    for (int i = start; i < end; i++){
        if (array[i] <= pivot){
            pointer++;
            elem = array[pointer];
            array[pointer] = array[i];
            array[i] = elem;
        }
    }
    elem = array[pointer + 1];
    array[pointer + 1] = array[end];
    array[end] = elem;
    return pointer + 1;
}

void quicksort(int* array, int start, int end)
{
    int border;
    if (start < end){
        border = partition(array, start, end);
        quicksort(array, border + 1, end);
        quicksort(array, start, border - 1);
    }
}

int SortedChecker(const int* array, int N)
{
    for (int i = 0; i < (N - 1); i++){
        if (array[i] > array[i + 1]){
            return 0;
        }
    }
    return 1;
}

int* ArrayGenerator(int N)
{
    int* array;
    array = (int*)malloc((N) * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < N; i++){
        array[i] = rand() % 1000000;
    }
    return array;
}

int* ArrayCopy(const int* array, int N)
{
    int* copied;
    copied = (int*)malloc((N) * sizeof(int));
    for (int i = 0; i < N; i++){
        copied[i] = array[i];
    }
    return copied;
}

int SortingTimeComparing(int* array, int N)
{
    clock_t start;
    clock_t end;
    double used_time;
    int* array2 = ArrayCopy(array, N);
    int* array3 = ArrayCopy(array, N);
    start = clock();
    slow_transposing_sort(array, N);
    end = clock();
    if (!SortedChecker(array, N)) {
    	printf("array isnt sorted.\n");
        free(array);
        free(array2);
        free(array3);
    	return 1;
    }
    used_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Sorting time by changing: %f sec\n", used_time);
    start = clock();
    quicksort(array2, 0, N - 1);
    end = clock();
    if (!SortedChecker(array2, N)) {
    	printf("array isnt sorted.\n");
        free(array);
        free(array2);
        free(array3);
    	return 2;
    }
    used_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Quicksorting time: %f sec\n", used_time);
    start = clock();
    qsort(array3, N, sizeof(int), compare);
    end = clock();
    if (!SortedChecker(array3, N)) {
    	printf("array isnt sorted");
        free(array);
        free(array2);
        free(array3);
    	return 3;
    }
    used_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("built-in sorting time: %f sec\n", used_time);
    free(array);
    free(array2);
    free(array3);
    return 0;
}

int compare(const void *a, const void *b) 
{
    return (*(int *)a - *(int *)b);
}