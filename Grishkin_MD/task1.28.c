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
    int temp;
    int maxSum;
    int curSum;
    int first;
    int next_elem;

      if (fscanf (file, "%d", &first)!= 1) {
            printf("файл пуст\n");
        return -2;
      }
    curSum = first;
    maxSum = curSum;
     while ((temp = fscanf(file, "%d", &next_elem) != EOF)) {
            if (curSum < 0) {
                curSum = 0;
            }
    curSum += next_elem;
    if (curSum > maxSum){
        maxSum = curSum;
       }
    }
     return maxSum;
 }

