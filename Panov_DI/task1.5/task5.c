#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int find_last_number_of_X(FILE *input);        //Функция, выполняющая вычисление номера последнего числа, равного X.

int find_last_number_of_X(FILE *input) {
    double current = 0;
    double X = 7;
    double epsilon = 0.001;
    int current_number = 0;
    int number_of_X = 0;

    if (fscanf(input, "%lf", &current) != 1) {
        printf("Не удается считать элемент\n");
			return -1;
    }

    current_number++;
    if (fabs(X - current) <= epsilon) {
        number_of_X = current_number;
    }

    while (fscanf(input, "%lf", &current) == 1) {
        current_number++;
        if (fabs(X - current) <= epsilon) {
            number_of_X = current_number;
        }
    } 

    if (feof (input) == 0){
		printf("Файл не прочитался до конца\n");
		return -1;
	}

    return number_of_X;
}

int main(void) {
    int last_number_of_X;
    FILE *input;

    input = fopen("/Users/dmitrij/Documents/GitHub/110-2023/Panov_DI/task1.5/test5.txt", "r");
    if(input == NULL)
	{
		printf("Не удается открыть файл\n");
		return -1;
	}

    last_number_of_X = find_last_number_of_X(input);

    if (last_number_of_X == 0) {
        printf("В последовательности нет чисел равных X\n");
    } else if (last_number_of_X > 0) {
        printf("Номер последнего числа, равного X: %d\n", last_number_of_X);
    }

    fclose(input);

    return 0;
}