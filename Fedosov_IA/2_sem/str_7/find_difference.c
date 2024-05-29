#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "find_difference.h"


int max(int x, int y) {
    if (x > y) {
        return x;
    } 
    return y;
}

int countLinesInFile(const char* filename, int max_length) {
    FILE *file;
    int count = 0;
    char* buffer = (char*)malloc(max_length * sizeof(char));

    file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++; 
    }

    fclose(file);
    free(buffer);

    return count;
}



int maxLineLengthInFile(const char* filename) {
    FILE *file;
    char *buffer = NULL;
    size_t buffer_size = 0;
    size_t read;
    int max_length = 0;

    file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    while ((read = getline(&buffer, &buffer_size, file)) != -1) {
        if (read > max_length) {
            max_length = read;
        }
    }

    fclose(file);
    free(buffer);

    return max_length;
}

// Функция для считывания строк из файла
int readLinesFromFile(const char* filename, char** lines, int max_length, int max_lines, Error *error) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    int lineCount = 0;
    while (fgets(lines[lineCount], max_length, file) != NULL && lineCount < max_lines) {
        lineCount++;
    }

    fclose(file);
    return lineCount;
}

// Функция для сравнения строк
int compareLines(char lineA[], char lineB[]) {
    return strcmp(lineA, lineB) == 0;
}

int find_difference(const char* filenameA, const char* filenameB, const char* fout, Error *error) {
    if (maxLineLengthInFile(filenameA) == -1 || maxLineLengthInFile(filenameB) == -1) {
        *error = INP;
        return 1;
    }
    int max_length = max(maxLineLengthInFile(filenameA), maxLineLengthInFile(filenameB));
    
    int max_lines = max(countLinesInFile(filenameA, max_length), countLinesInFile(filenameB, max_length));
    char** linesA = (char**)malloc(max_lines * sizeof(char*));
    char** linesB = (char**)malloc(max_lines * sizeof(char*));
    for (int i = 0; i < max_lines; i++) {
        linesA[i] = (char*)malloc(max_length* sizeof(char));
        linesB[i] = (char*)malloc(max_length * sizeof(char));
    }
    FILE* output = fopen(fout, "w");
    if (output == NULL) {
        *error = OUTP;
        return 1;
    }

    int lineCountA = readLinesFromFile(filenameA, linesA, max_length, max_lines, &error);
    int lineCountB = readLinesFromFile(filenameB, linesB, max_length, max_lines, &error);
    
    fprintf(output,"Строки, которые были удалены из файла A:\n");
    for (int i = 0; i < lineCountA; i++) {
        int found = 0;
        for (int j = 0; j < lineCountB; j++) {
            if (compareLines(linesA[i], linesB[j])) {
                found = 1;
                break;
            }
        }
        if (!found) {
            fprintf(output, "- %s", linesA[i]);
        }
    }

    fprintf(output, "\nСтроки, которые были добавлены в файл A:\n");
    for (int i = 0; i < lineCountB; i++) {
        int found = 0;
        for (int j = 0; j < lineCountA; j++) {
            if (compareLines(linesB[i], linesA[j])) {
                found = 1;
                break;
            }
        }
        if (!found) {
            fprintf(output, "+ %s", linesB[i]);
        }
    }
    for(int i = 0; i < max_lines; i++) {
        free(linesA[i]);
        free(linesB[i]);
    }
    *error = OK;
    fclose(output);
    free(linesA);
    free(linesB);

}
