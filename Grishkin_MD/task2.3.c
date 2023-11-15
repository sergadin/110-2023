#include <stdio.h>

void reverseArray(int arr[], int length) {
    int start = 0;
    int end = length - 1;
    int temp;

    while (start < end) {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        start++;
        end--;
    }
}

int main(void) {
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Ошибка открытия файла.\n");
        return 1;
    }

    int length;
    fscanf(file, "%d", &length);  

    int arr[length];

    for (int i = 0; i < length; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    fclose(file);

    printf("Исходный массив: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    reverseArray(arr, length);  

    printf("Переставленный массив: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}