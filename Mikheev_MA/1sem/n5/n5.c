#include <stdio.h>
#include <stdlib.h>
#define SUCCESS 0
#define ER_READ -1
#define ER_MEMORY -2


int segment(double *mas, int length);  //  функция заменяет элементы каждого x-отрезка на полусумму элементов, прилегающих к этому отрезку справа и слева.

int segment(double *mas, int length){
    
    double cur, min = 0, max;
    int j=0;
    int i=0;
    
    while(i < length){
        cur = mas[i];
        if(mas[i] == mas[i + 1]){
            i++;
            continue;
        }
        else{
            j = i;
            max = mas[i + 1];
            while(mas[j] == cur){
                mas[j] = 0.5 * (min + max);
                j--;
            }
            min = cur;
            i++;
        }
    }
    return SUCCESS;
}


int main(void)
{
    FILE* input;
    FILE* output;
    double *mas = NULL;  // массив
    int length;  // длина массива 
    int i=0;  // счетчик
    int res;  // результат работы функции
    
    input = fopen("input.txt", "r");
    if(input == NULL){
        printf("Ошибка чтения файла\n");
        return ER_READ;
    }
    
    output = fopen("output.txt", "w");
    if(output == NULL){
        printf("Ошибка чтения файла\n");
        return ER_READ;
    }
    
    
    if((fscanf(input, "%d", &length)) != 1){
        printf("Ошибка введенного массива\n");
        return ER_READ;
    }
    
    mas = (double*) malloc((length) * sizeof(double));
    
    if(mas == NULL){
        printf("Ошибка памяти\n");
        free(mas);
        return ER_MEMORY;
    }
    
    for(i = 0; i < length; i++){
        if((fscanf(input, "%lf", &mas[i])) != 1){
            printf("Ошибка чтения файла\n");
            free(mas);
            return ER_READ;
        }
    }
    
    
    res = segment(mas, length);
    
    if(res == SUCCESS){
        for(i = 0; i < length; i++){
            fprintf(output, "%lf ", mas[i]);
        }
        fprintf(output, "\n");
        free(mas);
        return SUCCESS;
    }
}