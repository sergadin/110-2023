#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


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
        printf("file pust or size not int");
        return -1;
    }

    arr = (int *)malloc(size * sizeof(int));

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


    if (arr == NULL){
        printf("memory error 1");
        return -2;
    }

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




int Sdvig(int arr[], int lgth){
    int i,j,k;
    int index;
    int len;
    for(i = 0; i < lgth; i++ ){
        for(j = lgth - 1; j > i; j--){
            if(arr[j] == arr[i]){
                index = j;
                len = lgth;
                for(k = index; k < len - 1; k++){
                    arr[k] = arr[k+1];
                }
                lgth--;
            }
        }
    }
    return lgth;
}

