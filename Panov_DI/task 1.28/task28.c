#include <stdio.h>

double find_max_sum(FILE *input); //функция, определяющая максимальную сумму подряд идущих элементов последовательности

double find_max_sum(FILE *input) {
    double first_element, next_element;
    double sum, max_sum;

    if (fscanf(input, "%lf", &first_element) != 1) {
        printf("Не удается считать элемент\n");
			return -1;
    } 

    sum = first_element;
    max_sum = sum;

    while (fscanf(input, "%lf", &next_element) == 1) {

        if (sum < 0) {
            sum = 0;
        }

        sum += next_element;
        if (sum > max_sum) {
            max_sum = sum;
        }
    }
    
    if (feof (input) == 0){
		printf("Файл не прочитался до конца\n");
		return -1;
    }

    return max_sum;
}

int main() {
    double result;
    FILE *input;

    input = fopen("/Users/dmitrij/Desktop/Учеба/task28/test28.txt", "r");

    if(input == NULL)
	{
		printf("Не удается открыть файл\n");
		return -1;
	}

    result = find_max_sum(input);

    if (result > 0) {
        printf("Максимальная сумма подряд идуших элементов последовательности равна %lf", result);
    }

    fclose(input);

    return 0;
}




    





