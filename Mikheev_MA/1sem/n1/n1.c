#include <stdio.h>
#define er_read -1
#define er_open -2
#define success 0


int last_num(FILE *input);
int last_num(FILE *input)//функция определяет номер последнего числа, который равен минимуму последовательности
{
    int i=1;//счетчик чисел
    int num=1;//номер конечного числа
    int rd;//переменная rd создана для проверки корректности данных файла
    double scan, min;
    rd = fscanf(input, "%lf", &min);
    if(rd != 1){
            return er_read;
    }
    while((rd = fscanf(input, "%lf", &scan)) != EOF ){
        if(rd != 1){
            return er_read;
        }
        i = i + 1;
        if(min >= scan){
            min = scan;
            num = i;
        }
    }
    return num;
}


int main(void)
{
   FILE *input;
    int res;
    input = fopen("input.txt", "r");
    if(input == NULL){
        printf("Не удалось открыть файл\n");
        return er_open;
    }
    res = last_num(input);
    if(res == er_read){
        printf("Ошибка введенной последовательности\n");
        return er_read;
    }
    printf("Номера числа %d \n", res);
    return success;
}