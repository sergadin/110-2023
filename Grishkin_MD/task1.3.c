#include <stdio.h>

double calculateHarmonicMean(FILE* file);
double mean; 
int main(void) {
	FILE *foutput, *finput;
    finput = fopen("input.txt", "r");

    if (finput == NULL) {
        printf("Не удалось открыть файл.\n");
        return 1;
    }
    mean = calculateHarmonicMean(finput);
    foutput = fopen("output.txt", "w");
    fprintf ( foutput, "Среднее гармоническое: %.2lf\n", mean);
	    
    fclose(finput);
    fclose(foutput);

    return 0;
}

double calculateHarmonicMean(FILE* finput) {
    int number;
    int count = 0;
    double sum = 0.0;

    while (fscanf(finput, "%d", &number) == 1) {
        sum += 1.0 / number;
        count++;
    }
     if  (count == 0) {
        printf("Файл пуст.\n");
	return -1;
     }
    return count / sum;
}




