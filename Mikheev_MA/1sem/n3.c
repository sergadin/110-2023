#include <stdio.h>
#include <math.h>

int main(void)
{
    double e = 0.1;
    double x, y, delt;
    int read = 0;
    FILE *input;
    input = fopen("input.txt", "r");
    if(input == NULL){
        printf("Не удалось открыть файл\n");
        return -1;
    }
    fscanf(input, "%lf", &x);
    while((read = fscanf(input, "%lf", &y)) != EOF){
        delt = fabs(x - y);
         if(read != 1){
            printf("Ошибка введенной последовательности\n");
            return -1;
         }
        if(delt <= e){
            x = y;
            continue;
        }
        else{
            printf("Присутствуют хотя бы 2 неравных числа\n");
            return -1;
        }
    }
            printf("Все числа равны с точностью до e\n");
            return 0;
}