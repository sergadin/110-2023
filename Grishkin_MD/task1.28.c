#include <stdio.h>

int findMaxSum(FILE *fin);
int result;
int main(void) {
	FILE *fout, *fin;
    fin = fopen("input.txt", "r");

    if (fin == NULL) {
        printf("Не удалось открыть файл!\n");
        return -1;
    }
    result = findMaxSum(fin);

    fout = fopen("output.txt", "w");
    fprintf(fout , "Максимальная сумма подряд идущих элементов: %d\n", result);

    fclose(fout);
    fclose(fin);
    return 0;
}

int findMaxSum(FILE *fin) { 
    int maxSum = -10000;
    int currentSum = 0;
    int number;

    while (fscanf(fin, "%d", &number) == 1) {
        currentSum += number;
        if (currentSum > maxSum) {
            maxSum = currentSum;
        }
    }

    return maxSum;
}

