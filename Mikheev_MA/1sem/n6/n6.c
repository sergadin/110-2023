
#include <stdio.h>
#include <stdlib.h>
#define ER_READ -1
#define ER_MEMORY -2
#define NOT_SUCCESS -3
#define SUCCESS 0


int segment(int *mas, int length);  // функция получает на входе массив и его длину, на выходе определяет, является ли массив плотным

int segment(int *mas, int length)
{
    int j=0;  // счетчик
    
    while(j < (length - 1)){
        if((mas[j] + 1) == mas[j + 1]){
            j++;
        }
        else{
            return NOT_SUCCESS;
        }
    }
    return SUCCESS;
}

int main(void)
{
    FILE* input;
    int *mas = NULL;  // массив
    int length;  // длина массива
    int i=0;  // счетчик
    int res;  // результат работы функции
    
    input = fopen("input.txt", "r");
    if(input == NULL){
        printf("Ошибка чтения файла\n");
        return ER_READ;
    }
    
    
    if((fscanf(input, "%d", &length)) != 1){
        printf("Ошибка введенного массива\n");
        return ER_READ;
    }
    
    mas = (int*) malloc((length) * sizeof(int));
    
    if(mas == NULL){
        printf("Ошибка памяти\n");
        free(mas);
        return ER_MEMORY;
    }
    
    for(i = 0; i < length; i++){
        if((fscanf(input, "%d", &mas[i])) != 1){
            printf("Ошибка чтения файла\n");
            free(mas);
            return ER_READ;
        }
    }
    
    res = segment(mas, length);
    
    if(res == NOT_SUCCESS){
        printf("Массив не является плотным\n");
        free(mas);
        return NOT_SUCCESS;
    }
    
    if(res == SUCCESS){
        printf("Массив является плотным\n");
        free(mas);
        return SUCCESS;
    }
}