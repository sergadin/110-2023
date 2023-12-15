#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

int Intersection(int arr_1[], int arr_2[], int size_1, int size_2);

int compare(const void* i, const void* j){
    return (*(int*)i - *(int*)j);
}


int main(){
    FILE *f1;
    FILE *f2;
    int size_1, size_2;
    int *arr_1;
    int *arr_2;
    int i;
    int flag;
    f1 = fopen("test.txt","r");
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
        printf("first file pust");
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

    Intersection(arr_1, arr_2, size_1, size_2);

    fclose(f1);
    fclose(f2);
    free(arr_1);
    free(arr_2);

    return 0;
}


int Intersection(int arr_1[], int arr_2[], int size_1, int size_2){
    int size_3;
    int *arr_3;
    int i;
    int k;
    clock_t start, end;

    size_3 = size_1 + size_2;
    arr_3=(int *)malloc(size_3 * sizeof(int));
    if(arr_3 == NULL){
        printf("memory error 3");
        return -3;
    }
    for(i = 0; i < size_1; i++){
        arr_3[i]=arr_1[i];
    }
    for(i = 0; i < size_2; i++){
        arr_3[i+size_1]=arr_2[i];
    }

    start = clock();
	qsort(arr_3, size_3, sizeof(int), compare);

    i=0;
    while(i < size_3-1){
        if(arr_3[i+1] == arr_3[i]){
            for(k = i; k < size_3 - 1; k++){
                arr_3[k]=arr_3[k+1];
            }
            size_3--;
        }
        else{
            i++;
        }
    }
    end = clock();

    printf("%.31f\n", ((float)(end-start))/CLOCKS_PER_SEC);
    for(i=0; i < size_3; i++){
        printf("%d ",arr_3[i]);
    }

    free(arr_3);

    return 0;
}







