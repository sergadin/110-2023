#include <stdio.h>
#include <stdlib.h>

int is_element_good(double * array_B, int len_B, double A_value, int A_index);

int main(void){
	FILE *fin_A, *fin_B, *fout;
    int len_A, len_B;
    double *array_A = NULL, *array_B = NULL;
    int counter = 0;
    int flag = -1;


	if ((fin_A = fopen("inA.txt", "r")) == NULL){
		return -1;
	}

	if ((fin_B = fopen("inB.txt", "r")) == NULL){
		fclose(fin_A);
		return -1;
        }

	if ((fout = fopen("output.txt", "w")) == NULL){
		fclose(fin_A);
		fclose(fin_B);
        return -1;
        }

	if((fscanf(fin_A, "%d", &len_A) != 1) || (fscanf(fin_B, "%d", &len_B) != 1)){
        fclose(fin_A);
		fclose(fin_B);
        fclose(fout);
        return -1;
    }
    
    if (len_A < 1 || len_B < 1){
        fclose(fin_A);
		fclose(fin_B);
        fclose(fout);
        return -1;
    }
        
    
    array_A = (double*)malloc(len_A * sizeof(double));
    for(int i = 0; i < len_A; i++){
        if(fscanf(fin_A, "%lf", &array_A[i]) != 1){
            fclose(fin_A);
            fclose(fin_B);
            fclose(fout);
            free(array_A);
            return -1;
        }
    }
    
    array_B = (double*)malloc(len_B * sizeof(double));
    for(int i = 0; i < len_B; i++){
        if(fscanf(fin_B, "%lf", &array_B[i]) != 1){
            fclose(fin_A);
            fclose(fin_B);
            fclose(fout);
            free(array_A);
            free(array_B);
            return -1;
        }
       
    }
    
    flag = -1;
    for (int i = 0; i < len_A; i++){
        if((flag = is_element_good(array_B, len_B, array_A[i], i)) == 1){
            counter++;
        }
    }
    
    fprintf(fout, "%d ", counter);
    
    flag = -1;
    for (int i = 0; i < len_A; i++){
        if((flag = is_element_good(array_B, len_B, array_A[i], i)) == 1){
            fprintf(fout, "%lf ", array_A[i]);
        }
    }
    
    fclose(fin_A);
    fclose(fin_B);
    fclose(fout);
    free(array_A);
    free(array_B);
}

int is_element_good(double * array_B, int len_B, double A_value, int A_index){
    double sum_of_B = 0;
    if (A_index < len_B){
        for (int i = 0; i <= A_index; i ++){
            sum_of_B += array_B[i];
        }
    
        if (A_value > sum_of_B){
            return 1;
        } else {
            return -1;
        }
    }
    
    if (A_index >= len_B){
        for (int i = 0; i < len_B; i ++){
            sum_of_B += array_B[i];
        }
    
        if (A_value > sum_of_B){
            return 1;
        } else {
            return -1;
        }
    }
    return -1;
}
    
    
        










