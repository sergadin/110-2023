#include <stdio.h>

int findMaxSum(FILE *file);
int result;
int main(void) {
    FILE *file = fopen("input.txt", "r");

    if (file == NULL) {
        printf("Не удалось открыть файл!\n");
        return -1;
    }
    result = findMaxSum(file);
    if (result == 0) {
	    printf("в файле нет последовательности или все элементы равны 0\n");
    }
    else {
            printf("Максимальная сумма подряд идущих элементов: %d\n", result);
    }
    fclose(file);
    return 0;
}

int findMaxSum(FILE *file) {
    int maxSum = 0;
    int currentSum = 0;
    int number;

    while (fscanf(file, "%d", &number) == 1) {
        currentSum += number;
        
        if (currentSum > maxSum) {
            maxSum = currentSum;
        }
        
        if (currentSum < 0) {
            currentSum = 0;
        }
    }

    return maxSum;
}

