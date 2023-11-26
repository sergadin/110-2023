#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int function(FILE *input);        //Функция, выполняющая вычисление номера числа, равного X.

int function(FILE *input) {
    double a = 0;
    double x = 7;
    double epsilon = 0.001;
    int count = 0;
    int n = 0;
    if (fscanf(input, "%lf", &a) != 1) {
        printf("Не удается считать элемент\n");
			return -1;
    }
    count++;
    if (fabs(x - a) <= epsilon) {
        n = count;
    }
    while (fscanf(input, "%lf", &a) == 1) {
        count++;
        if (fabs(x - a) <= epsilon) {
            n = count;
        }
    }  
    return n;
}

int main() {
    int y;
    FILE *input;
    input = fopen("/Users/dmitrij/Desktop/Учеба/test files/test5.txt", "r");
    if(input == NULL)
		{
			printf("Не удается открыть файл\n");
			return -1;
		}
    y = function(input);
    if (y == 0) {
        printf("В последовательности нет чисел равных X\n");
    } else if (y > 0) {
        printf("Номер последнего числа, равного X: %d\n", y);
    }
    fclose(input);
    return 0;
}