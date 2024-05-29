#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formate.h"

// функция возвращает максимальную длину строки в файле
int maxLineLengthInFile(const char* filename) {
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    int max_length = 0;
    int length = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            if (length > max_length) {
                max_length = length;
            }
            length = 0;
        } else {
            length++;
        }
    }
    // Проверка последней строки, если нет завершающего \n
    if (length > max_length) {
        max_length = length;
    }

    fclose(file);
    return max_length;
}

// Функция возвращает длину самого длинного слова в файле
int maxWordLengthInFile(const char* filename) {
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    int max_length = 0;
    int length = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == ' ' || ch == '\n' || ch == '\t') {
            if (length > max_length) {
                max_length = length;
            }
            length = 0;
        } else {
            length++;
        }
    }
    // Проверка последнего слова, если нет завершающего разделителя
    if (length > max_length) {
        max_length = length;
    }

    fclose(file);
    return max_length;
}

// функция считывает количество строк в файле
int countLinesInFile(const char* filename) {
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    int count = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            count++;
        }
    }
    // Если файл не заканчивается новой строкой, нужно добавить одну строку
    fseek(file, -1, SEEK_END);
    if (fgetc(file) != '\n') {
        count++;
    }

    fclose(file);
    return count;
}

// функция форматирует получившийся абзац
void formatParagraph(char paragraph[], int width, FILE* outp) {
    int first_line = 1;
    char *word;
    int remaining_width = width;
    fprintf(outp, "    ");
    word = strtok(paragraph, " \n");
    while (word != NULL) {
        int word_length = strlen(word);
        if (first_line) {
            fprintf(outp, "    ");
            remaining_width -= 4;
            first_line = 0;
        }
        if (word_length > remaining_width) {
            fprintf(outp, "\n    ");
            remaining_width = width - 4;
        }
        fprintf(outp, "%s ", word);
        remaining_width -= word_length + 1;
        word = strtok(NULL, " \n");
    }
    fprintf(outp, "\n");
}

// основная функция
int formate(const char* filenameA, const char* fout, int width, Error *error) {
    FILE *file, *outp;
    char *buffer = NULL;
    size_t buffer_size = 0;
    size_t read;
    char *paragraph = NULL;
    size_t paragraph_size = 0;

    file = fopen(filenameA, "r");
    if (file == NULL) {
        *error = INP;
        return 1;
    }

    outp = fopen(fout, "w");
    if (outp == NULL) {
        fclose(file);
        *error = OUTP;
        return 1;
    }

    paragraph = (char *)malloc(1);
    paragraph[0] = '\0';

    while ((read = getline(&buffer, &buffer_size, file)) != -1) {
        if (strcmp(buffer, "\n") == 0) {  // Пустая строка - конец абзаца
            if (strlen(paragraph) > 0) {
                formatParagraph(paragraph, width, outp);
                free(paragraph);
                paragraph = (char *)malloc(1);
                paragraph[0] = '\0';
                fprintf(outp, "\n");
            }
        } else {
            size_t new_size = strlen(paragraph) + strlen(buffer) + 1;
            paragraph = (char *)realloc(paragraph, new_size);
            strcat(paragraph, buffer);
        }
    }

    if (strlen(paragraph) > 0) {  // Форматируем последний абзац, если он есть
        formatParagraph(paragraph, width, outp);
    }

    free(paragraph);
    free(buffer);
    fclose(file);
    fclose(outp);

    *error = OK;
    return 0;
}
