#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SUCCESS 0
#define ER_READ -1
#define ER_MEMORY -2
#define MORE_EPS -3
#define LESS_EPS -4


int segment(double *mas, int length); //  функция заменяет элементы каждого x-отрезка на полусумму элементов, прилегающих к этому отрезку справа и слева.
int eps(double *first, double * second);


int eps(double *first, double *second){ // сравнивает 2 числа с точностью до е = 0.01
    double eps = 0.01;
    if(fabs(*first - *second) < eps){
        return LESS_EPS;
    }
    return MORE_EPS;
}

int segment(double *mas, int length){
    double x = 20, min = 0, max = 0;
    int i = 0, j = 0, k = 0;
    
    for(i = 0; i < length; i++){
        if(eps(&mas[i], &x) == MORE_EPS){
            continue;
        }
        if(i == 0){
            min = 0;
        }
        else{
            min = mas[i - 1];
        }
        
        j = i;
        
        while(eps(&mas[j], &x) == LESS_EPS){
            j++;
        }
        if(j == length - 1){
            max = 0;
        }
        else{
            max = mas[j];
        }
        
        for(k = j - 1; k >= i; k--){
            if(k == length - 1){
                max = 0;
            }
            mas[k] = (max + min) / 2;
        }
        
        i = j;
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
        fclose(input);
        return ER_READ;
    }
    
    
    if((fscanf(input, "%d", &length)) != 1){
        printf("Ошибка введенного массива\n");
        fclose(input);
        fclose(output);
        return ER_READ;
    }
    
    mas = (double*) malloc((length) * sizeof(double));
    
    if(mas == NULL){
        printf("Ошибка памяти\n");
        fclose(input);
        fclose(output);
        free(mas);
        return ER_MEMORY;
    }
    
    for(i = 0; i < length; i++){
        if((fscanf(input, "%lf", &mas[i])) != 1){
            printf("Ошибка чтения файла\n");
            fclose(input);
            fclose(output);
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
        fclose(input);
        fclose(output);
        free(mas);
        return SUCCESS;
    }
}