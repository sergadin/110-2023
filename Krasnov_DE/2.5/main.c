#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


int main(){
    FILE *f1;
    FILE *f2;
    int size_1, size_2, size_3;
    int *arr_1;
    int *arr_2;
    int *arr_3;
    int i;
    int flag;
    int size;
    f1 = fopen("input(1).txt","r");
    f2 = fopen("input(2).txt","r");

    if(f1==NULL){
        printf("oshibka chteniya");
        return -1;
    }

    if(f2 == NULL){
        printf("oshibka chteniya");
        return -1;
    }

    if((flag=fscanf(f1,"%d",&size_1))!=1){
        printf("first file pust or size not int");
        return -1;
    }

    if((flag=fscanf(f2,"%d",&size_2))!=1){
        printf("second file pust");
        return -1;
    }

    arr_1=(int *)malloc(size_1 * sizeof(int));

    if(arr_1 == NULL){
        printf("memory error 1");
        return -1;
    }

    arr_2=(int *)malloc(size_2 * sizeof(int));

    if(arr_2 == NULL){
        printf("memory error 2");
        return -3;
    }
    for(i = 0; i < size_1; i++){
        flag=fscanf(f1, "%d", &arr_1[i]);
        if(flag!=1){
            printf("est not int or kol-vo elementov<razmera in firs file");
            return -1;
        }
    }

    for(i = 0; i < size_2; i++){
        flag=fscanf(f2, "%d", &arr_2[i]);
        if(flag!=1){
            printf("est not int or kol-vo elementov<razmera in second file");
            return -1;
        }
    }

    size_3=size_1+size_2;

    arr_3=(int *)malloc(size_3 * sizeof(int));

    if(arr_3 == NULL){
        printf("memory error 3");
        return -3;
    }

    for(i = 0; i < size_1; i++){
        arr_3[i]=arr_1[i];
        printf("%d ",arr_3[i]);
    }
    printf("\n");

    for(i = 0; i < size_2; i++){
        arr_3[i+size_1]=arr_2[i];
        printf("%d ",arr_3[i+size_1]);
    }
    printf("\n");
    size = DeleteItem(arr_3,size_3);
    arr_3 = (int *)realloc(arr_3, size * sizeof(int));
    if(arr_3 == NULL){
        printf("memory error 3");
        return -1;
    }

    for(i=0; i < size; i++){
        printf("%d ",arr_3[i]);
    }
    fclose(f1);
    fclose(f2);
    free(arr_3);



    return 0;
}


int DeleteItem(int arr[], int lgth){
    int i,j,k,len;
    int index;
    for(i=0; i < lgth; i++ ){
        for(j = lgth - 1; j > i; j--){
            if(arr[j]==arr[i]){
                index = j;
                len=lgth;
                for(k = index; k < len - 1; k++){
                    arr[k]=arr[k+1];
                }
                lgth--;
            }
        }
    }
    return lgth;

}
