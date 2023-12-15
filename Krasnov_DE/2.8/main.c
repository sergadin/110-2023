#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>


int Function(float arr[/*x*/], int x);

int main(void){
    FILE *f1;
    FILE *f2;
    int size, i, flag, l;
    int *arr;
    int quantity_not_zero=0;
    int quantity=0;
    f1 = fopen("input.txt","r");
    f2 = fopen("input.txt","r");

    if(f1==NULL){
        printf("oshibka chteniya");
        return -1;
    }

    while((flag = fscanf(f2, "%d", &l)) != EOF){
        if(flag != 1){
            printf("est not int");
            return -1;
        }
        quantity++;
    }

    if(fscanf(f1, "%d", &size)!=1){
        printf("file pust");
        return -1;
    }

    if(quantity <= size){
        printf("kol-vo elementov < razmera massiva");
        return -1;
    }

    arr=(int *)malloc(size * sizeof(int));

    if (arr == NULL){
        printf("memory error 1");
        return -2;
    }

    for(i = 0; i < size; i++){
        fscanf(f1, "%d", &arr[i]);
    }

    quantity_not_zero = Zanulenie(arr,size);
    Function(arr, size);
    size = quantity_not_zero;
    arr=(int *)realloc(arr, size * sizeof(int));
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
    fclose(f2);
    free(arr);


    return 0;
}



int Function(float arr[/*x*/], int x){
    int j = 0;
    for (int i = 0; i < x; ++i) {
        if (arr[i] != 1.5) {
            assert(j <= i);
            arr[j++] = arr[i];
        }
    }
    for (; j < x; ++j) {
        arr[j] = 1.5;
    }
}



int Zanulenie(float arr[], int x){
    int n, i, quantity_not_zero;
    for(i = 0; i < x; i++){
        for(n = 1; n + i < x; n++){
            if(arr[i] == arr[i + n])
                arr[n + i]= 1.5;

        }
    }
    for(i = 0; i < x; i++){
        if(arr[i] != 1.5){
            quantity_not_zero++;
        }
    }
    return quantity_not_zero;


}

