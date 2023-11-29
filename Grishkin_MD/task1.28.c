#include <stdio.h>

int findMaxSum(FILE *file);

int main(void) {
    int result;

	FILE *file = fopen("input.txt", "r");

    if (file == NULL) {
        printf("Не удалось открыть файл\n");
        return -1;
    }
    result = findMaxSum(file);

    printf("Максимальная сумма подряд идущих элементов: %d\n", result);

    fclose(file);

    return 0;
}

 int findMaxSum(FILE *file) {
    int maxSum;
    int curSum;
    int first;
    int next;

      if (fscanf (file, "%d", &first) != 1) {
            printf("файл пуст\n");
        return -2;
      }
    curSum = first;
    maxSum = curSum;
     while (fscanf(file, "%d", &next) == 1) {
            if (curSum < 0) {
                curSum = 0;
            }
    curSum += next;
    if (curSum > maxSum) {
        maxSum = curSum;
       }
    }
     return maxSum;
 }

