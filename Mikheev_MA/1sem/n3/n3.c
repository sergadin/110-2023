#include <stdio.h>
#include <math.h>
#define er_open -1 //ошибка открытия
#define er_read -2 //ошибка чтения
#define not_success -3 //файл не удовлетворяет условиям
#define success 0 //все хорошо


int func1(FILE *input);
int func1(FILE *input) //функция проверяет равенство чисел последовательности с точностью до e(в данном случае e=0.1)
{
    double e = 0.1;
    double scan_1, scan_2, delt; //scan_1 и scan_2 числа которые сравнивает программа, delt - их разница
    int rd; //переменная rd создана для проверки корректности файла и данных файла
    rd = fscanf(input, "%lf", &scan_1);
    if (rd != 1){
        return er_read;
    }
    while((rd = fscanf(input, "%lf", &scan_2)) != EOF){
        delt = fabs(scan_1 - scan_2);
        if(rd != 1){
            return er_read;
        }
        if(delt <= e){
            scan_1 = scan_2;
            continue;
        }
        else{
            return not_success;
        }
    }
    return success;
    
}


int main()
{
    FILE *input;
    int res;
    input = fopen("input.txt", "r");
    if(input == NULL){
        printf("Не удалось открыть файл\n");
        return er_open;
    }
    res = func1(input);
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