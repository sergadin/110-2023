#include <stdio.h>
#define SUCCESS 0
#define ER_READ -1
#define ER_OPEN -2

int count_of_units(int n){ // функция на входе получает количество единиц, которое должно соержать число, печатает все числа с нужным количеством единиц, если таких чисел нет, то напечатано будет ничего
    int i = 0; // счетчик количества переменных в числе
    int min = 10; // переменная минимума диапазона
    int max = 30; // перменная максимума диапазона
    int current; // переменная текущего числа, которое проверяют
    int check; // число которое сдвигают
    for(current = min; current < max; current++){
        int i = 0;
        check = current;
        while(check > 0){
            if(check & 1){
                i++;
            }
            check = check >> 1;
        }
        if(i == n){
            printf("%d\n", current);
        }
    }
    return SUCCESS;
}


int main(void)
{
    int n;
    
    FILE* input;
    input = fopen("input.txt", "r");
    if(input == NULL){
        printf("Ошибка открытия файла\n");
        return ER_OPEN;
    }
  
    if((fscanf(input, "%d", &n)) != 1){
        printf("Ошибка чтения файла\n");
        fclose(input);
        return ER_READ;
    }
  
    count_of_units(n);
    
    return SUCCESS;
}

