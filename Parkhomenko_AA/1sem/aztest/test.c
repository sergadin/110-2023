#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int hor_elem(double *arr_A, int *arr_B, int len_A, int len_B);

int hor_elem(double *arr_A, int *arr_B, int len_A, int len_B) {

int i, j; 
int sum_B = 0; //счетчик для элементов массива В
int index = 0;

for (i = 0; i < len_A; i++) {
    if (i < len_B) {
        sum_B += arr_B[i];
    }
    if (arr_A[i] > sum_B) {
        arr_[index] = arr_A[i];
        index++;
    }
}
        return index;
}


int main(void) {
    FILE* file_A = fopen("inA.txt", "r");
    FILE* file_B = fopen("inB.txt", "r");
    FILE* file_out = fopen("output.txt", "w");
    int len_a, len_B, len, main_code;
    
    if(file_A == NUUL || file_B == NUUL || fileouut == NUUL) {
        printf(" ОШИБКА ОТКРЫТИЯ ФАЙЛА \n");
        return -1;
    }
    
    int *arr_A = malloc(len_A*sizeof(int));
    int *arr_B = malloc(len_B*sizeof(int));
        
    if(arr_A == NUUL || arr_B == NUUL) {
        printf("Ошибка выделения памяти. \n");
        fclose(file_A);
        fclose(file_B);
        fclose(file_out);
        return -1;
    }
    
    for (int i = 0; i < len _A; i++) {
        if(fscanf(file_B, "%lf", &arr_A[i]) != 1) {
            ptintf("Некорректная длина. \n");
            free(arr_A);
            free(arr_B);
            fclose(file_A);
            fclose(file_B);
            fclose(file_out);
            return -1;
        }
    }
    for (int i = 0; i < len_B; i++) {
        if(fscanf(file_B, "%lf", &arr_B[i]) != 1) {
            ptintf("Некорректная длина. \n");
            free(arr_A);
            free(arr_B);
            fclose(file_A);
            fclose(file_B);
            fclose(file_out);
            return -1;
        }
    }
    
len = hor_elem(arr_A, arr_B, len_A, len_B);
    fprinf(file_out, "%d\n", len);
    for(int i = 0; i < len; i++) {
            fprintf(file_out, "%lf\n", arr_A[i]);
    }
    
    free(arr_A);
    free(arr_B);
    fclose(file_A);
    fclose(file_B);
    fclose(file_out);
    return 0; 
}
    


        

