#include <stdio.h>
#include <stdlib.h>

int good_elem(double *A, double *B, int len1, int len2);
int good_elem(double *A, double *B, int len1, int len2){
    
    double summa =0.;
    int count = 0;
    for(int i = 0; i<len1; i++){
        if (i<len2){
            summa+=B[i];
            //printf("%lf\n", summa);
            if (A[i]>summa){
                //printf("ok - A[%d] - %lf\n", i, A[i]);
                A[count] = A[i];
                count++;
                
            }
            
        }else{
            A[i] = 0.;
        }

        
    }
    return count;
}







int main(void){
    int len1, len2, len, main_term; 
    FILE *f_in_A, *f_in_B, *f_out;
    double *arrA= NULL, *arrB=NULL;
    
    f_in_A = fopen("inA.txt","r");
    if (f_in_A == NULL){
        printf("File is empty\n");
        return -1;
    }
     f_in_B = fopen("inB.txt","r");
     if (f_in_B == NULL){
        printf("File is empty\n");
        fclose(f_in_A);
        return -1;
    }
     
     f_out = fopen("output.txt","w");
     if (f_out == NULL){
        printf("File is empty\n");
        fclose(f_in_A);
        fclose(f_in_B);
        return -1;
    }
     if ((fscanf(f_in_A, "%d", &len1)!=1) || len1==0){
         printf("uncorrect len\n");
         main_term = -1;
         goto term;
        }
    if ((fscanf(f_in_B, "%d", &len2)!=1) || len2 ==0){
         printf("uncorrect len\n");
         main_term = -1;
         goto term;
        }
    
    arrA = (double *)malloc(len1*sizeof(double));
    if (arrA==NULL){
        printf("memory err\n");
        main_term =-1;
        goto term;
        
    }
    arrB = (double *)malloc(len2*sizeof(double));
    if (arrB==NULL){
        printf("memory err\n");
        main_term =-1;
        free(arrA);
        goto term;
        
    }
    
    for (int i=0; i<len1; i++){
        if (fscanf(f_in_A, "%lf", &arrA[i])!=1){
            printf("uncorrect len or value in file_A\n");
            main_term = -1;
            goto term1;
        }
    }
    for (int i=0; i<len2; i++){
        if (fscanf(f_in_B, "%lf", &arrB[i])!=1){
            printf("uncorrect len or value in file_B\n");
            main_term = -1;
            goto term1;
        }
    }
    
    len = good_elem(arrA, arrB, len1, len2);
    fprintf(f_out, "%d\n", len);
    for (int i = 0; i<len; i++){
            fprintf(f_out, "%lf\n", arrA[i]);
        
    }
    
    term1:
    free(arrA);
    free(arrB);
    
    term:
    
    fclose(f_in_A);
    fclose(f_in_B);
    fclose(f_out);
    
    return main_term;

}
