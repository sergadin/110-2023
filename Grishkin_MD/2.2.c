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
        printf("ne udalos'ortrit' file \n");
        return 1;
    }
    fscanf(file, "%d", &lenght);
    arr = (int*)malloc(lenght * sizeof(int));

    if (arr == NULL) {
        printf("memory error\n");
        fclose(file);
        return -1;
    }
    for (int i = 0; i < lenght; i++) {
        if (fscanf(file, "%d", &arr[i]) != 1){
            printf("lenght не соответствует длине массива\n");
            return -2;
        }
    }

    fclose(file);

    printf("array: ");
    for (int i = 0; i < lenght; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    reverseArray(arr, lenght);

    printf("Reversed array: ");
    for (int i = 0; i < lenght; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}