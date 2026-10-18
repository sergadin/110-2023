#include "compare_files.h"

void compare_files(char linesA[MAX_LINES][MAX_LINE_LENGTH], int countA,
                   char linesB[MAX_LINES][MAX_LINE_LENGTH], int countB) {
    int i, j;
    int found;

    printf("Changes from file A to file B:\n");

    // Проверяем строки из файла A
    for (i = 0; i < countA; i++) {
        found = 0;
        for (j = 0; j < countB; j++) {
            if (strcmp(linesA[i], linesB[j]) == 0) {
                found = 1; // Строка найдена в файле B
                break;
            }
        }
        if (!found) {
            printf("Line %d in file A removed: %s\n", i + 1, linesA[i]);
        }
    }

    // Проверяем строки из файла B
    for (j = 0; j < countB; j++) {
        found = 0;
        for (i = 0; i < countA; i++) {
            if (strcmp(linesB[j], linesA[i]) == 0) {
                found = 1; // Строка найдена в файле A
                break;
            }
        }
        if (!found) {
            printf("Line %d in file B added: %s", j + 1, linesB[j]);
        }
    }
}
