#include <stdio.h>
#include <stdlib.h>

int is_array_happy(int arr[], int length);

int is_array_happy(int arr[], int length) {
    int sum = 0;
    int curSum = 0;

    for (int i = 0; i < length; i++) {
        sum += arr[i] ;
    }
    for (int i = 0; i < length; i++) {
            curSum +=arr[i];
            sum -= arr[i];
            if (sum == curSum){
                return 1;
            }
    }
    return 0;
}
int main(void) {
    int length;
    int* arr;
    int isHappy;
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

    isHappy = is_array_happy(arr, length);

  if(isHappy){
    printf("array happy");
  }
  else {
    printf("array unhappy");
  }

    return 0;
}
