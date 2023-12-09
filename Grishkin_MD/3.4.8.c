#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}
// ������� ��� ���������� ������� ����� ������� �������
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

// ������� ��� ���������� ������� ����� ������� ��������
void countingSort(int arr[], int length) {
    int output[length];
    int max = arr[0];
    for (int i = 1; i < length; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    int count[max + 1];
    memset(count, 0, sizeof(count));
    for (int i = 0; i < length; i++)
        count[arr[i]]++;
    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];
    for (int i = length - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    for (int i = 0; i < length; i++)
        arr[i] = output[i];
}

// ������� ��� �������� ������� �� ���������������
int isSorted(int arr[], int length) {
    for (int i = 1; i < length; i++) {
        if (arr[i] < arr[i - 1])
            return 0;
    }
    return 1;
}

// ������� ��� ������������� ���������� ������� ��������� �����
void generateRandomArray(int arr[], int length) {
    srand(time(NULL));
    for (int i = 0; i < length; i++)
        arr[i] = rand();
}

int main(void) {
    int length = 1000;  // ��������� ����� �������
    int repetitions = 5;  // ���������� ���������� �����
    double timeTaken;
    int* arr;
    for (int i = 0; i < repetitions; i++) {
        arr = (int*)malloc(length * sizeof(int));

        // ���������� ��������� ������
        generateRandomArray(arr, length);

        // �������� ����� ������ ��������� ���������� ��������
        clock_t startTime = clock();
        insertionSort(arr, length);
        clock_t endTime = clock();
        timeTaken = (double)(endTime - startTime) / CLOCKS_PER_SEC;
        printf("Insertion Sort: N = %d, Time taken: %f seconds\n", length, timeTaken);

        // ���������, ������������ �� ������
        if (!isSorted(arr, length))
            printf("Array not sorted by Insertion Sort\n");

        // �������� ����� ������ ��������� ���������� ���������
        startTime = clock();
        countingSort(arr, length);
        endTime = clock();
        timeTaken = (double)(endTime - startTime) / CLOCKS_PER_SEC;
        printf("Counting Sort: N = %d, Time taken: %f seconds\n", length, timeTaken);

        // ���������, ������������ �� ������
        if (!isSorted(arr, length))
            printf("Array not sorted by Counting Sort\n");

        // �������� ����� ������ ������������ ������� qsort
        startTime = clock();
        qsort(arr, length, sizeof(int), compare);
        endTime = clock();
        timeTaken = (double)(endTime - startTime) / CLOCKS_PER_SEC;
        printf("qsort: N = %d, Time taken: %f seconds\n", length, timeTaken);

        // ���������, ������������ �� ������
        if (!isSorted(arr, length))
            printf("Array not sorted by qsort\n");

        length *= 2;  // ��������� ����� ������� ��� ���������� �����
    }

    return 0;
}
