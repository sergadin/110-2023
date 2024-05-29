#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formate.h"


//функция возвращает максимальную длину строки в файле
int maxLineLengthInFile(const char* filename) {
    FILE *file;
    char *buffer = NULL;
    size_t buffer_size = 0;
    size_t read;
    int max_length = 0;

    file = fopen(filename, "r");

    while ((read = getline(&buffer, &buffer_size, file)) != -1) {
        if (read > max_length) {
            max_length = read;
        }
    }

    fclose(file);
    free(buffer);

    return max_length;
}


//Функция возвращает длину самого длинного слова в файле
int maxWordLengthInFile(const char* filename) {
    FILE *file;
    char *word = NULL;
    size_t word_size = 0;
    size_t read;
    int max_length = 0;

    file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    while ((read = getline(&word, &word_size, file)) != -1) {
        char *token = strtok(word, " \n"); // Разбиваем строку на слова
        while (token != NULL) {
            int length = strlen(token);
            if (length > max_length) {
                max_length = length;
            }
            token = strtok(NULL, " \n");
        }
    }

    fclose(file);
    free(word);

    return max_length;
}


//функция считывает количество строк в файле
int countLinesInFile(const char* filename, int max_length) {
    FILE *file;
    int count = 0;
    char buffer[1000]; 

    file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++; 
    }

    fclose(file);

    return count;
}

//функция форматирует получившийся абзац
void formatParagraph(char paragraph[], int width, FILE* outp) {
    int first_line = 1;
    char *word;
    int remaining_width = width;
    
    word = strtok(paragraph, " \n");
    while (word != NULL) {
        if (first_line) {
            fprintf(outp, "    ");
            remaining_width -= 4;
            first_line = 0;
        }
        int word_length = strlen(word);
        if (word_length > remaining_width) {
            fprintf(outp, "\n");
            remaining_width = width;
        }
        fprintf(outp, "%s ", word);
        remaining_width -= word_length + 1;
        word = strtok(NULL, " \n");
    }
    fprintf(outp, "\n");
}

//основная функция
int formate(const char* filenameA, const char* fout, int width, Error *error) {
    FILE *file, *outp;
    char* buffer;
    char* paragraph;
    int max_lines;
    int max_word_length;
    int max_line_length;

    // Открываем файл для чтения
    file = fopen(filenameA, "r");
    if (file == NULL) {
        *error = INP;
        return 1;
    }
    outp = fopen(fout, "w");
    if (outp == NULL) {
        *error = OUTP;
        return 1;
    }

    max_line_length = maxLineLengthInFile(filenameA);
    max_word_length = maxWordLengthInFile(filenameA);
    buffer = (char*)malloc(max_word_length * sizeof(char));

    max_lines = countLinesInFile(filenameA, max_word_length);

    paragraph = (char*)malloc(max_lines * max_line_length * sizeof(char));

    // Считываем текст из файла
    paragraph[0] = '\0'; // Обнуляем строку абзаца
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strcmp(buffer, "\n") == 0) { // Если встречаем пустую строку
            if (strlen(paragraph) > 0) { // Если абзац не пустой
                formatParagraph(paragraph, width, outp); // Форматируем абзац
                paragraph[0] = '\0'; // Обнуляем строку абзаца для следующего абзаца
                fprintf(outp, "\n");
            }
        } else {
            strcat(paragraph, buffer); // Добавляем строку к текущему абзацу
        }
    }
    if (strlen(paragraph) > 0) { // Форматируем последний абзац, если он есть
        formatParagraph(paragraph, width, outp);
    }

    fclose(file);
    fclose(outp);
    free(paragraph);
    free(buffer);

    *error = OK;
    return 0;
}
