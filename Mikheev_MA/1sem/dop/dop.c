#include <stdio.h>
#include <stdlib.h>
#define PRINT_ZERO -1
#define ONE_ZERO 1
#define NON_ZERO -2
#define SUCCESS 0
#define ER_READ -3
#define ER_MEMORY -4

void k_element(int *mas, int length, FILE *output);
int how_many_zero(int *mas, int length, int *index);

int how_many_zero(int *mas, int length, int *index){
    int zero = 0;
    
    for(int i = 0; i < length; i++){
        if(mas[i] == 0){
            *index = i;
            zero++;
        }
    }
    
    return zero;
}

void k_element(int *mas, int length, FILE *output){
    int zeros;
    int M = 1;
    int index = 0;
    
    zeros = how_many_zero(mas, length, &index);
    
    if(zeros > 1){
        for(int j = 0; j < length; j++){
            fprintf(output, "0\n");
        }
    }
    
    if(zeros == 1){
        for(int i = 0; i < length; i++){
            if(i != index){
                M = M * mas[i];
            }
        }
        for(int j = 0; j < length; j++){
            if(j != index){
                fprintf(output, "0\n");
                continue;
            }
            fprintf(output, "%d\n", M);
        }
    }
    
    if(zeros < 1){
        for(int i = 0; i < length; i++){
                M = M * mas[i];
        }
        for(int j = 0; j < length; j++){
            fprintf(output, "%d\n", M / mas[j]);
        }
    }
}



int main(void)
{
    FILE* input;
    FILE* output;
    int *mas = NULL;  // массив
    int length;  // длина массива
    int i=0;  // счетчик
    
    input = fopen("input.txt", "r");
    if(input == NULL){
        printf("Ошибка чтения файла\n");
        return ER_READ;
    }
    
    output = fopen("output.txt", "w");
    if(input == NULL){
        printf("Ошибка чтения файла\n");
        fclose(input);
        return ER_READ;
    }
    
    
    if((fscanf(input, "%d", &length)) != 1){
        printf("Ошибка введенного массива\n");
        fclose(input);
        fclose(output);
        return ER_READ;
    }
    
    mas = (int*) malloc((length) * sizeof(int));
    
    if(mas == NULL){
        printf("Ошибка памяти\n");
        fclose(input);
        fclose(output);
        return ER_MEMORY;
    }
    
    for(i = 0; i < length; i++){
        if((fscanf(input, "%d", &mas[i])) != 1){
            printf("Ошибка чтения файла\n");
            fclose(input);
            fclose(output);
            free(mas);
            return ER_READ;
        }
    }
    
    k_element(mas, length, output);
    
    fclose(output);
    fclose(input);
    free(mas);
    return SUCCESS;
    
}
    
    
    
    

