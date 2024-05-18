#include "strings.h"

void copyWords(const char* input_filename, const char* output_filename) {
    FILE* input_file = fopen(input_filename, "r");
    FILE* output_file = fopen(output_filename, "w");

    if (input_file == NULL) {
        perror("Ошибка открытия входного файла");
        return;
    }
    if (output_file == NULL) {
        perror("Ошибка открытия выходного файла");
        fclose(input_file);
        return;
    }

    int ch;
    char word[256];  // Буфер для хранения текущего слова
    int index = 0;

    while ((ch = fgetc(input_file)) != EOF) {
        if (isspace((unsigned char)ch) || ispunct((unsigned char)ch)) {
            if (index > 0) {
                word[index] = '\0';  // Завершаем строку
                fprintf(output_file, "%s\n", word);  // Записываем слово в выходной файл
                index = 0;  // Сбрасываем индекс для нового слова
            }
        }
        else {
            word[index++] = (char)ch;  // Добавляем символ к текущему слову
        }
    }

    // Проверяем, есть ли слово в буфере после окончания чтения файла
    if (index > 0) {
        word[index] = '\0';
        fprintf(output_file, "%s\n", word);
    }

    fclose(input_file);
    fclose(output_file);
}