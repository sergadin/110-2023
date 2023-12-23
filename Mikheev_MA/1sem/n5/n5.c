#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SUCCESS 0 
#define ER_READ -1
#define ER_OPEN -2
#define ER_MEMORY -3

void segment(double *mas, int length, double x);
int eps(double a, double b);

int eps(double a, double b){ // функция сравнивает числа с точностью до e
    double e = 0.1;
    if(fabs(a - b) < e){
        return 1;
    }
    return 0;
}


void segment(double *mas, int length, double x){ // фунция на входе получает массив, длину, значение х-отрезка, заменяет все х-отрезки на полусумму прилегающих
    double min = 0;
    double max = mas[1];
    
    for(int i = 0; i < length; i++){
        if(eps(mas[i], x) != 1){
            continue;
        }
        
        min = mas[i - 1];
        
        int j = i;
        
        while(eps(mas[j + 1], x) == 1){
            j++;
        }
        if(j == length - 1){
            max = 0;
        }
        else{
            max = mas[j + 1];
        }
        
        for(int k = j; eps(mas[k], x) == 1; k--){
            mas[k] = (max + min) / 2;
        }
        
        i = j - 1;
    }
    
}



int main(void)
{
    FILE *input;
    FILE *output;
    double *mas = NULL;
    double scan;
    int rd;
    int length = 0;
    double x = 20;
    
    
    input = fopen("input.txt", "r");
    
    if(input == NULL){
        printf("Ошибка открытия файла\n");
        return ER_OPEN;
    }
    
    output = fopen("output.txt", "w");
    
    if(output == NULL){
        fclose(input);
        return ER_OPEN;
    }
    
    while((rd = fscanf(input, "%lf", &scan)) != EOF){
        length++;
        if(rd != 1){
            fclose(input);
            fclose(output);
            return ER_READ;
        }
    }
    
    if(length == 0){
        fclose(input);
        fclose(output);
        return ER_READ;
    }
    
    
    mas = (double*) malloc(length * sizeof(double*));
    
    if(mas == NULL){
        fclose(input);
        fclose(output);
        return ER_MEMORY;
    }
    
    rewind(input);
    
    for(int i = 0; i < length; i++){
        fscanf(input, "%lf", &mas[i]);
    }
    
    for(int j = 0; j < length; j++){
        printf("%lf\n", mas[j]);
    }
    
    segment(mas, length, x);
    
    for(int j = 0; j < length; j++){
        fprintf(output, "%lf ", mas[j]);
    }
    
    fclose(input);
    fclose(output);
    free(mas);
    return SUCCESS;
}