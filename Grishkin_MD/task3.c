#include <stdio.h>

double calculateHarmonicMean(FILE* file);
double mean;
double calculateHarmonicMean(FILE* file) {
    int number;
    int count = 0;
    double sum = 0.0;

    while (fscanf(file, "%d", &number) == 1) {
        sum += 1.0 / number;
        count++;
    }

    if (count == 0) {
        printf("Файл пуст.\n");
        return -1.0;
    }

    return count / sum;
}


int main(void) {
    FILE* file = fopen("input.txt", "r");
    
    if (file == NULL) {
        printf("Не удалось открыть файл.\n");
        return 1;
    }
    mean = calculateHarmonicMean(file);
    printf("Среднее гармоническое: %.2lf\n", mean);
    
    fclose(file);
    return 0;
}



