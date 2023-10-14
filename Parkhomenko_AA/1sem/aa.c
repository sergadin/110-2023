#include <stdio.h>
int checkSequence(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла\n");
        return -1;
    }
    
    int currentNum, prevNum;
    int isIncreasing = 1;
    // флаг для проверки возрастающей последовательности
    
    int isDecreasing = 1; 
    // флаг для проверки убывающей последовательности

    if (fscanf(file, "%d", &prevNum) != 1) {
        printf("Файл пуст\n");
        fclose(file);
        return -1;
    }

    while (fscanf(file, "%d", &currentNum) == 1) {
        if (currentNum > prevNum) {
            isDecreasing = 0;
        } else if (currentNum < prevNum) {
            isIncreasing = 0; 
        }
        prevNum = currentNum;
    }

    fclose(file);

    if (isIncreasing && !isDecreasing) {
        return 1; 
        // последовательность возрастающая
    } else if (!isIncreasing && isDecreasing) {
        return -1; 
        // последовательность убывающая
    } else {
        return 0; 
        // последовательность не является ни возрастающей, ни убывающей
    }
}

int main() {
    char filename[100];
    printf("Введите последовательность: ");
    scanf("%s", filename);

    int result = checkSequence(filename);
    if (result == 1) {
        printf("Последовательность является возрастающей\n");
    } else if (result == -1) {
        printf("Последовательность является убывающей\n");
    } else {
        printf("Последовательность не является ни возрастающей, ни убывающей\n");
    }

    return 0;
}

// используя цикл, считываем числа из файла по одному и сравниваем их с предыдущим числом
//  функция "checkSequence" открывает файл, считывает числа и проверяет, является ли последовательность возрастающей или убывающей
// функция "main" запрашивает имя файла у пользователя и вызывает "checkSequence", чтобы определить характеристику последовательности. 
// currentNum" и "prevNum" - это переменные, которые используются для хранения текущего и предыдущего чисел последовательности соответственно