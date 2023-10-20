#include <stdio.h>

int findMaxSum(FILE *file);
int result;

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
int main(void) {
    FILE *file = fopen("input.txt", "r");
    
    if (file == NULL) {
        printf("Не удалось открыть файл!\n");
        return 1;
    }
    
    result = findMaxSum(file);
    
    printf("Максимальная сумма подряд идущих элементов: %d\n", result);
    
    fclose(file);
    return 0;
}
