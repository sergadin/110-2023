#include <math.h>
#include <stdio.h>
#define er_read -1
#define er_open -2
#define success 0

int derivative(FILE* input, double* value, double* value_der);//функция на входе получает коэффиценты многочлена, а на выходе определяет значение многочлена при Х(в данном случае х=2) и значение производной

int derivative(FILE* input, double* value, double* value_der)
{
    int rd;//переменная создана для проверки корректности файла
    double scan;//переменная, которая считывает элементы файла
    int i = 0;//счетчик
    double x = 2;//значение точки, в которой ищем значение многочлена
    int position = 0;//позиция возвращения указателя
    
    rd = fscanf(input, "%lf", &scan);
    if(rd != 1){
        return er_read;
    }
    fseek(input, position, SEEK_SET);
    
    while((rd = fscanf(input, "%lf", &scan)) != EOF){
        if(rd != 1){
            return er_read;
        }
        if(i == 0){
            *value = scan;
            i++;
            continue;
        }
        *value = *value + scan * pow(x, i);
        *value_der = *value_der + scan * i * pow(x, i - 1);
        i++;
    }
    return success;
}

int main(void)
{
    FILE* input;
    int res;
    double value = 0;//значение многочлена в точке Х
    double value_der = 0;//значение производной в точке Х
    
    input = fopen("input.txt", "r");
    if(input == NULL){
        printf("Ошибка открытия файла\n");
        return er_open;
    }
    
    res = derivative(input, &value, &value_der);
    
    if(res == er_read){
        printf("Ошибка введенной последовательности\n");
        return er_read;
    }
    if(res == success){
        printf("Значение функции в точке X - %lf\nЗначение производной в точке X - %lf\n", value, value_der);
        return success;
    }
}