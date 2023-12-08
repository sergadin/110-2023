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

    Sdvig(arr, size);

    for(i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }

    fclose(f1);
    free(arr);


    return 0;
}




int Sdvig(int arr[], int lgth){
    int i;
    int len;
    int b;
    for(i = lgth - 1; i > 0; i--){
        if(arr[i] < 0 ){
            len = lgth;
            b=arr[i];
            for(i; i < len - 1; i++){
                arr[i] = arr[i+1];
            }
            arr[len-1]=b;
            lgth--;
        }
    }
    return 0;
}
