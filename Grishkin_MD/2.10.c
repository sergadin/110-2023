#include <stdio.h>
#include <stdlib.h>
void removeNegative(int arr[], int length, int* newLength);

void removeNegative(int arr[], int length, int* newLength) {
    int  count = 0;

    for (int i = 0; i < length; i++) {
        if (arr[i] >= 0) {
            arr[count] = arr[i];
            count++;
        }
    }

    *newLength = count;
}

int main(void) {
    int length, newLength;
    int* arr;
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("file opening error\n");
        return 1;
    }
    fscanf(file, "%d", &length);
    arr = (int*)malloc(length * sizeof(int));
    if (arr == NULL){
           printf("memory error\n");
           return -1;
    }
    for (int i = 0; i < length; i++) {
        if(fscanf(file, "%d", &arr[i]) != 1){
           printf("length ne rovna dline massiva\n");
        return -2;
        }
    }

    fclose(file);

    removeNegative(arr, length, &newLength);

    printf("newArray: \n");
    for (int i = 0; i < newLength; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n number of remaining values: %d\n", newLength);

    return 0;
}
