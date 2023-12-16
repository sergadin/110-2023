#include <stdio.h>
#include <stdlib.h>


int unit_arrays(int * array_A,int len_A, int * array_B, int len_B, int * array_C);
//функция объединяет 2 массива как числовые множества и возращает длину получившегося массива


int add_uniq_elements(int * array_A, int len_A, int * array_C, int amount);
//функция, добавляющая в массив уникальные элементы из другого массива


int main(void){
	int len_A, len_B, len_C;
	int * array_A = NULL, * array_B = NULL, * array_C;
	FILE *fin, *fout;
	int i;
	
	fin = fopen("input.txt", "r");
	if (fin == NULL){
		printf("не удалось открыть файл 'input.txt'\n");
		fclose(fin);
		return -1;
	}

	fout = fopen("output.txt", "w");
        if (fout == NULL){
            printf("не удалось открыть файл 'output.txt'\n");
            fclose(fin);
            fclose(fout);
            return -1;
        }
        
        if (fscanf(fin, "%d %d", &len_A, &len_B) == 0){
            printf("ошибка входных данных\n");
            fclose(fin);
            fclose(fout);
		return -1;
	}
	
	array_A = (int *)malloc(len_A * sizeof(int));
	array_B = (int *)malloc(len_B * sizeof(int));
	
	for (i = 0; i < len_A; i++){
		if (fscanf(fin, "%d", &array_A[i]) != 1){
			printf("неверные входные данные для массива\n");
			fclose(fin);
            fclose(fout);
			free(array_A);
			free(array_B);
			return -1;
		}
	}
	
	for (i = 0; i < len_B; i++){
		if (fscanf(fin, "%d", &array_B[i]) != 1){
			printf("неверные входные данные для массива\n");
			fclose(fin);
            fclose(fout);
			free(array_A);
			free(array_B);
			return -1;
		}
	}
		
	len_C = len_A + len_B;
	
	array_C = (int *)malloc(len_C * sizeof(int));
	
	len_C = unit_arrays(array_A, len_A, array_B, len_B, array_C);
    
    if (len_C == -1){
        fclose(fin);
        fclose(fout);
        free(array_A);
        free(array_B);
        return -1;
    }
        
	
	fprintf(fout, "%d\n", len_C);
	
	for(i = 0; i < len_C; i++){
		fprintf(fout, "%d ", array_C[i]);
	}
	
	fclose(fin);
	fclose(fout);
	free(array_A);
	free(array_B);
	
	return 0;
}


int unit_arrays(int * array_A, int len_A, int * array_B, int len_B, int * array_C){
    int len_C;
    int num1; //num2;
    int amount_in_C = 1;
    
    
    if (len_A != 0){
        array_C[0] = array_A[0];
    } else if(len_B != 0){
        array_C[0] = array_B[0];
    } else {
        printf("данные массивы пусты\n");
        return -1;
    }
    
    num1 = add_uniq_elements(array_A, len_A, array_C, amount_in_C);
    
    amount_in_C = num1;
    
    //num2 = add_uniq_elements(array_B, len_B, array_C, amount_in_C);
    
    len_C = add_uniq_elements(array_B, len_B, array_C, amount_in_C);
    
    return len_C;
    
}


int add_uniq_elements(int * array_A, int len_A, int * array_C, int amount){
    int i, k;
	int counter = amount; //переменная для подсчета количества элементов в получившемся массиве
	int repeating_elements = 0;
	
	for(i = 0; i < len_A; i++){
        repeating_elements = 0;
		for(k = 0; k < counter; k++){
			if (array_A[i] == array_C[k]){
				repeating_elements += 1;
			}
		}
		if (repeating_elements == 0){
			array_C[counter] = array_A[i];
			counter++;
		}
	}
	
	return counter;
}
    
    
	
			
		
	
	
	


	
	
	
	
	
	
	
	
	
	
	


	

