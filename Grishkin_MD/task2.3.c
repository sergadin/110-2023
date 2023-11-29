#include <stdio.h>
void reverseArray(int arr[], int length);

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
    int lenght;
    int* arr;
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Ошибка открытия файла.\n");
        return 1;
    }
    fscanf(file, "%d", &lenght);
    arr = malloc(lenght * sizeof(int));

    if (arr == NULL) {
        printf("память не выделена\n");
        fclose(file);
        return -1;
    }
    for (int i = 0; i < lenght; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    fclose(file);

    printf("Исходный массив: ");
    for (int i = 0; i < lenght; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    reverseArray(arr, lenght);

    printf("Переставленный массив: ");
    for (int i = 0; i < lenght; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
}

