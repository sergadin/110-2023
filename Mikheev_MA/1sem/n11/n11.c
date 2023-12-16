#include <stdio.h>
#include <stdlib.h>
#define ER_OPEN -1
#define ER_READ -2
#define ER_MEMORY -3
#define SUCCESS_SEGMENT -4
#define NOT_SUCCESS_SEGMENT -5

int result_segment(double *mas_left, double *mas_right, int length){ // функция находит объединение всех отрезков
    double max = mas_right[0]; // минимум среди верхних границ, те итоговый максимальный элемент объединения отрезков
    double min = mas_left[0]; // максимум среди нижних границ, те итоговый минимальный элемент объединения отрезков
    int i;
    
    for(i = 0; i < (length / 2); i++){
        if (mas_left[i + 1] > mas_left[i]){
            min = mas_left[i + 1];
        }
    }
    
    for(i = 0; i < (length / 2); i++){
        if (mas_right[i + 1] < mas_right[i]){
            max = mas_right[i + 1];
        }
    }
    
    
}


int correct_of_segment(double *mas_left, double *mas_right, int length){ // функция проверяет, чтобы вдруг не встретился отрезок, в котором левая граница больше правой
    for(int i = 0; i < (length / 2); i++){
        if(mas_left[i] > mas_right[i]){
            return NOT_SUCCESS_SEGMENT;
        }
    }
    return SUCCESS_SEGMENT;
}

int main(void)
{
    FILE *input;
    double *mas_left = NULL; // массив левых границ отрезков
    double *mas_right = NULL; // массив правых границ отрезков
    int length;
    
    input = ("input.txt", "r")
    if(input == NULL){
        printf("Ошибка открытия файла\n");
        return ER_OPEN;
    }
    
    if((fscanf(input, "%d", length)) != 1){
        printf("Некорректная длина массива\n");
        fclose(input);
        return ER_READ;
    }
    
    if(length < 0){
        printf("Некорректная длина массива\n");
        fclose(input);
        return ER_READ;
    }
    
    if(length % 2 !=0){
        printf("Некорректная длина массива\n");
        fclose(input);
        return ER_READ;
    }
    
    mas_left = (double*) malloc((length / 2) * sizeof(double*));

    if(mas_left == NULL){
        printf("Ошибка памяти\n");
        fclose(input);
        return ER_MEMORY;
    }
    
    mas_right = (double*) malloc((length / 2) * sizeof(double*));
    
    if(mas_right == NULL){
        printf("Ошибка памяти\n");
        fclose(input);
        free(mas_left);
        ER_MEMORY;
    }
    
    for(int i = 0; i <= (length / 2); i++){
        if((fscanf(input, "%lf" "%lf", &mas_left[i], &mas_right[i])) != 1){
            printf("Ошибка введенного массива\n");
            free(mas_right);
            free(mas_left);
            fclose(input);
            return ER_READ;
        }
    }
    
    int res;
    
    res = correct_of_segment(mas_left, mas_right, length);
    
    if(res == NOT_SUCCESS_SEGMENT){
        printf("Введены некорректные отрезки\n");
        fclose(input);
        free(mas_right);
        free(mas_left);
        return NOT_SUCCESS_SEGMENT;
    }
    
    
    
    
    
}
