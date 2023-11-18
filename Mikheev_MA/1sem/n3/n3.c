#include <stdio.h>
#include <math.h>
#define er_open -1 //ошибка открытия
#define er_read -2 //ошибка чтения
#define not_success -3 //файл не удовлетворяет условиям
#define success 0 //все хорошо


int compare(FILE *input);
int compare(FILE *input) //функция проверяет равенство чисел последовательности с точностью до e(в данном случае e=0.1)
{
    double e = 0.1;
    double scan_1, scan_2; //scan_1 и scan_2 числа которые сравнивает программа
    double max, min; //переменные созданы, чтобы создать максимальность и маскимальность отклонений относительно первого числа
    int rd; //переменная rd создана для проверки корректности файла и данных файла
    rd = fscanf(input, "%lf", &scan_1);
    max = scan_1 + e;
    min = scan_1 - e;
    if (rd != 1){
        return er_read;
    }
    while((rd = fscanf(input, "%lf", &scan_2)) != EOF){
        if(rd != 1){
            return er_read;
        }
        if(scan_2 < max && scan_2 > min){
            if (scan_2 <= scan_1){
                max = scan_2 + e;
            }
            if (scan_2 >= scan_1){
                min = scan_2 - e;
            }
            continue;
        }
        else{
            return not_success;
        }
    }
    return success;
    
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
    res = compare(input);
    if(res == er_read){
        printf("Ошибка введенной последовательности\n");
        return er_read;
    }
    if(res == not_success){
        printf("Присутствуют хотя бы 2 неравных числа\n");
        return not_success;
    }
    if(res == success){
        printf("Все числа равны с точностью до e\n");
        return success;
    }
}
