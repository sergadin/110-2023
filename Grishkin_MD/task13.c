#include <stdio.h> 
 
int findLastMinIndex(FILE* file); 
 
int main() { 
    FILE* file = fopen("input.txt", "r"); 
     
    if (file == NULL) { 
        printf("Не удалось открыть файл.\n"); 
        return 1; 
    } 
     
    int index = findLastMinIndex(file); 
    printf("Номер последнего числа, равного минимуму: %d\n", index); 
     
    fclose(file); 
    return 0; 
} 
 
int findLastMinIndex(FILE* file) { 
    int number, min, index, lastIndex = -1; 
     
    if (fscanf(file, "%d", &min) != 1) { 
        printf("Файл пуст.\n"); 
        return -1; 
    } 
     
    index = 0; 
    while (fscanf(file, "%d", &number) == 1) { 
        if (number <= min) { 
            min = number; 
            lastIndex = index; 
        } 
        index++; 
    } 
     
    return lastIndex; 
}
