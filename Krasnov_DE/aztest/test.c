#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

float summa(double arr[],int i, int len_1, int len_2);

int Sdvig (double arr_1[],double  arr_2[],int len_1, int len_2);


float summa(double arr[],int  i, int len_1, int len_2){
    float s=0;
    int j=0;
    if(len_1==len_2){
        for(j=0;j<=i;j++){
            s=s+arr[j];
        }
    }
    else{
        for(j=0;j<=len_2;j++){
            s=s+arr[j];
        }
    }
    return s;
}

int Sdvig (double arr_1[], double arr_2[], int len_1, int len_2){
    int i;
    int lgth;
    int k;
    for(i=0;i<len_1;i++){
        if(arr_1[i] < summa(arr_2, i, len_1, len_2)){
            len_1=lgth;
            for(k=i;k < len_1-1;k++){
                arr_1[k]=arr_1[k+1];
            }
            lgth--;
        }
    }
    return lgth;
}
            

int main(void){
    FILE *f1;
    FILE *f2;
    FILE *output;
    int i;
    int size;
    int len_1;
    int len_2;
    double *arr_1, *arr_2;
    f1=fopen("inA.txt","r");
    f2=fopen("inB.txt","r");
    output=fopen("output.txt","w");
    if(f1==NULL){
        return -1;
    }
    if(f2==NULL){
        return -1;
    }
    if((fscanf(f1,"%d",&len_1))!=1){
        return -1;
    }
    if((fscanf(f2,"%d",&len_2))!=1){
        return -1;
    }
    arr_1 = (double *)malloc(len_1 * sizeof(double));
    arr_2 = (double *)malloc(len_2 * sizeof(double));
    if(arr_1 == NULL){
        fclose(f1);
        fclose(f2);
        return -1;
    }
    if(arr_1 == NULL){
        fclose(f1);
        fclose(f2);
        return -1;
    }
    for(i=0;i<len_1;i++){
        if( (fscanf(f1,"%lf",&arr_1[i]))!=1){
            fclose(f1);
            fclose(f2);
            return -1;
        }
    }
    for(i = 0; i < len_2; i++){
       if( (fscanf(f1,"%lf",&arr_2[i]))!=1){
           return -1;
           
       }
    }
    size = Sdvig(arr_1,arr_2,len_1, len_2);
    arr_1 = (double *)realloc(arr_1, size * sizeof(double));
    for(i=0;i < size;i++){
        fprintf(output,"%lf",arr_1[i]);
    }
    fprintf(output,"\n%d",size);
    
    

    return 0;
}
