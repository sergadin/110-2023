#include "PosOfWord.h"


int PosOfWord(FILE* input, Er *error, const char *word){
    
    char *line = NULL; 
    size_t length;
    int read;
    int line_number = 0;
    int counter = 0; // количество обнаруженных слов
    *error = OK;


    while ((read = getline(&line, &length, input)) != -1) {
        if(line == NULL){
            *error = MEMORY; 
        }
        line_number++;
        char *pos = line;
        
        while ((pos = strstr(pos, word)) != NULL) {
            printf("Строка %d Позиция %ld\n", line_number, pos - line + 1); 
            pos = pos + 1;
            counter++;
        }
    }
    
    free(line);

    return counter;
}
