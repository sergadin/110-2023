#include <stdio.h> 
 
int findLastMinIndex(FILE* finput); 
int result;
int main(void) {
       FILE *finput, *foutput;	
     finput = fopen("input.txt", "r"); 
     
    if (finput == NULL) { 
        printf("Не удалось открыть файл.\n"); 
        return 1; 
    } 
    result = findLastMinIndex(finput);

    foutput = fopen ("output.txt", "w");
    if (foutput == NULL) {
	    printf("не удалось открыть файл для вывода\n");
	    return 2;

    if (result == -1) {
	   printf("файл пуст\n");
    }
    else { 
           fprintf(foutput, "Номер последнего числа, равного минимуму: %d\n", result); 
    } 
    fclose(finput);
    fclose(foutput); 
    return 0; 
} 
 
int findLastMinIndex(FILE* finput) {

    int number;
    int min;
    int index = 0;
    int lastIndex = -1; 
     
    if (fscanf(finput, "%d", &min) != 1) { 
        printf("Файл пуст.\n"); 
        return -1; 
    } 
     
    index = 0; 
    while (fscanf(finput, "%d", &number) == 1) { 
        if (number <= min) { 
            min = number; 
            lastIndex = index;
	}
	index++;
     }

    return lastIndex; 
}
