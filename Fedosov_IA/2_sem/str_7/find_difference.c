#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "find_difference.h"

// Функция для сравнения строк
int compareLines(const char* lineA, const char* lineB) {
    return strcmp(lineA, lineB) == 0;
}

void find_difference(const char* filenameA, const char* filenameB, const char* fout, Error *error) {
    FILE *fileA;
    FILE *fileB;
    FILE *output;
    char *lineA = NULL;
    char *lineB = NULL;
    size_t lenA = 0;
    size_t lenB = 0;


    fileA = fopen(filenameA, "r");
    fileB = fopen(filenameB, "r");
    output = fopen(fout, "w");
    if (fileA == NULL || fileB == NULL) {
        *error = INP;
        if (fileA)
            fclose(fileA);
        if (fileB)
            fclose(fileB);
        return;
    }

    if (output == NULL) {
        *error = OUTP;
        fclose(fileA);
        fclose(fileB);
        return;
    }

    fprintf(output, "Строки, которые были удалены из файла A:\n");

    while (getline(&lineA, &lenA, fileA) != -1) {
        int found = 0;
        fseek(fileB, 0, SEEK_SET);
        while (getline(&lineB, &lenB, fileB) != -1) {
            if (compareLines(lineA, lineB)) {
                found = 1;
                break;
            }
        }
        if (!found) {
            fprintf(output, "- %s", lineA);
        }
    }

    fseek(fileA, 0, SEEK_SET);
    fseek(fileB, 0, SEEK_SET);

    fprintf(output, "\nСтроки, которые были добавлены в файл A:\n");

    while (getline(&lineB, &lenB, fileB) != -1) {
        int found = 0;
        fseek(fileA, 0, SEEK_SET);
        while (getline(&lineA, &lenA, fileA) != -1) {
            if (compareLines(lineB, lineA)) {
                found = 1;
                break;
            }
        }
        if (!found) {
            fprintf(output, "+ %s", lineB);
        }
    }

    free(lineA);
    free(lineB);
    fclose(fileA);
    fclose(fileB);
    fclose(output);

    *error = OK;
}
