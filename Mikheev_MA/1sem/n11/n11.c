#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ER_OPEN -1
#define ER_READ -2
#define ER_MEMORY -3
#define SUCCESS_SEGMENT -4
#define NOT_SUCCESS_SEGMENT -5
#define SUCCESS 1
#define NOT_SUCCESS -6
#define MORE_EPS -7
#define LESS_EPS -8

double result_segment_left(double *mas_left, int length);
double result_segment_right(double *mas_right, int length);
int correct_of_segment(double *mas_left, double *mas_right, int length);
int inclusion_of_segment(double max, double min, double *mas_right, double *mas_left, int length);
void swap_elements(double *a, double *b);
int eps(double *first, double * second);

int eps(double *first, double *second){ // сравнивает 2 числа с точностью до е = 0.01
    double eps = 0.01;
    if(fabs(*first - *second) < eps){
        return LESS_EPS;
    }
    return MORE_EPS;
}



void sort_left_limit(double *mas_left, double *mas_right, int length){ // функция упорядычивает отрезки по левой границе
    int i;
    int j; 
    
    
    for(i = 0; i < (length / 2) - 1; i++){
        for(j = 0; j < (length / 2) - i - 1; j++){
           if(mas_left[j] > mas_left[j + 1]){
                double current = mas_left[j];
                mas_left[j] = mas_left[j + 1];
                mas_left[j + 1] = current;
            
                current = mas_right[j + 1];
                mas_right[j + 1] = mas_right[j];
                mas_right[j] = current;
            }
        }
    }
}



double result_segment_left(double *mas_left, int length){ // минимум среди левых границ
    double min = mas_left[0];
    int i;
    for(i = 0; i < (length / 2) - 1; i++){
        if (mas_left[i + 1] < mas_left[i]){
            min = mas_left[i + 1];
        }
    }
    return min;
}

double result_segment_right(double *mas_right, int length){ // максимум среди правых границ
    int i;
    double max = mas_right[0];
    
    for(i = 0; i < (length / 2) - 1; i++){
        if (mas_right[i + 1] > mas_right[i]){
            max = mas_right[i + 1];
        }
    }
    return max;
}

int correct_of_segment(double *mas_left, double *mas_right, int length){ // функция проверяет, чтобы вдруг не встретился отрезок, в котором левая граница больше правой
    for(int i = 0; i < (length / 2); i++){
        if(mas_left[i] > mas_right[i]){
            return NOT_SUCCESS_SEGMENT;
        }
    }
    return SUCCESS_SEGMENT;
}


int inclusion_of_segment(double max, double min, double *mas_right, double *mas_left, int length){ // функция определяет, покрывает ли объединение отрезков заданный отрезок [a , b] (находит "пробелы" в объединении отрезков и проверяет их наличие в заданном)
    double a = 500;
    double b = 1000;
    
    double high = mas_right[0];
    double low = mas_left[0];
    
    double vacuum_min; // минимумы и максимумы "пробелов"
    double vacuum_max;
    
    
    if((a < min) || (b > max)){
        return NOT_SUCCESS;
    }
    
    for(int i = 0; i < length / 2; i++){
        low = mas_left[i + 1];
        
        if(high > low || ((eps(&high, &low)) == LESS_EPS)){
            if(high < mas_right[i + 1]){
                high = mas_right[i + 1];
            }
            continue;
        }
        
        vacuum_max = low;
        vacuum_min = high;
        
        printf("minimum %lf\nmaximum %lf\n\n", vacuum_min, vacuum_max);
        
        if(((vacuum_min < b || eps(&vacuum_min, &b) == LESS_EPS) && (vacuum_min > a || eps(&vacuum_min, &a) == LESS_EPS))   
        ||   ((vacuum_max < b || eps(&vacuum_max, &b) == LESS_EPS) && (vacuum_max > a ||  eps(&vacuum_min, &a) == LESS_EPS))){
            return NOT_SUCCESS;
        }
        
        high = mas_right[i + 1];
    }
    
    return SUCCESS;
}



int main(void)
{
    FILE *input;
    double *mas_left = NULL; // массив левых границ отрезков
    double *mas_right = NULL; // массив правых границ отрезков
    int length; // длина заданного файла
    double min;
    double max;
    int result;
    
    input = fopen("input.txt", "r");
    if(input == NULL){
        printf("Ошибка открытия файла\n");
        return ER_OPEN;
    }
    
    if((fscanf(input, "%d", &length)) != 1){
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
        return ER_MEMORY;
    }
    
    for(int i = 0; i < (length / 2); i++){
        if((fscanf(input, "%lf %lf", &mas_left[i], &mas_right[i])) != 2){
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
    
    min = result_segment_left(mas_left, length);
    //printf("min - %lf\n", min);
    max = result_segment_right(mas_right, length);
    //printf("max - %lf\n", max);
    
    sort_left_limit(mas_left,mas_right,length);
    
    result = inclusion_of_segment(max, min, mas_right, mas_left, length);
    
    if(result == SUCCESS){
        fclose(input);
        free(mas_right);
        free(mas_left);
        printf("Покрывает\n");
        return SUCCESS;
    }
    
    fclose(input);
    free(mas_right);
    free(mas_left);
    printf("Не покрывает\n");
    return NOT_SUCCESS;
    
}

