#include <stdio.h> 
 
int findLastMinIndex(FILE* file); 
int result;
int main(void) { 
    FILE* file = fopen("input.txt", "r"); 
     
    if (file == NULL) { 
        printf("Не удалось открыть файл.\n"); 
        return 1; 
    } 
     
    result = findLastMinIndex(file);
    if (result == -1) {
	   printf("файл пуст\n");
    }
    else { 
    printf("Номер последнего числа, равного минимуму: %d\n", result); 
    } 
    fclose(file); 
    return 0; 
} 
 
int findLastMinIndex(FILE* file) { 
    int number, min, index = 0, lastIndex = -1; 
     
    if (fscanf(file, "%d", &min) != 1) { 
        printf("Файл пуст.\n"); 
        return -1; 
    } 
     
    index = 0; 
    while (fscanf(file, "%d", &number) == 1) { 
        if (number <= min) { 
            min = number; 
            index++;
	}
            lastIndex = index;  	
    }
     
    return lastIndex; 
}
