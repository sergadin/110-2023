#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void Sort(int arr[], int lgth);
int Sdvig(int arr[/*x*/], int lgth);

int main(void){
    FILE *f1;
    int size, i, flag, l;
    int *arr;
    f1 = fopen("input.txt","r");
    if(f1 == NULL){
        printf("oshibka chteniya");
        return -1;
    }
    if(fscanf(f1, "%d", &size) != 1){
        printf("file pust");
        return -1;
    }
    arr = (int *)malloc(size * sizeof(int));
     if (arr == NULL){
        printf("memory error 1");
        return -2;
    }
    for(i = 0; i < size; i++){
        flag = fscanf(f1, "%d", &arr[i]);
        if(flag != 1){
            printf("est not int or kol-vo elementov<razmera ");
            return -1;
        }
    }
    for(i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    size = Sdvig(arr, size);
    arr = (int *)realloc(arr, size * sizeof(int));
    if(arr == NULL){
        printf("memory error 2");
        return -3;
    }
    for(i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("%d", size);
    fclose(f1);
    free(arr);


    return 0;
}


void Sort(int arr[], int lgth){
    int i;
    int j;
    for (int i = 0; i < lgth - 1; i++){
        for (int j = (lgth - 1); j > i; j--){
            if (arr[j - 1] > arr[j]){
                int temp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}


int Sdvig(int arr[], int lgth){
    int i=0;
    int len;
    int k;
    Sort(arr, lgth);
    while(i < lgth-1){
        if(arr[i+1] == arr[i]){
            len = lgth;
            for(k = i; k < len - 1; k++){
                arr[k]=arr[k+1];
            }
            lgth--;
        }
        else{
            i++;
        }
    }
    return lgth;

}

