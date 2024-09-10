#include "PosOfWord.h"
#define YES 1 
#define NO 0


int isolation(char *start, char *end, char *line){ // проверка на изолированность слова
    if(start == line || !isalnum(*(start - 1))){
        if(*end == '\0' || !isalnum(*end)){
            return YES;
        }
    }
    
    return NO;
}


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
            char *end = pos + strlen(word);
            if(isolation(pos, end, line) == YES){
                printf("Строка %d Позиция %ld\n", line_number, pos - line + 1);
                counter++;
            }
            pos = pos + 1;
            //counter++;
        }
    }
    
    free(line);

    return counter;
}
