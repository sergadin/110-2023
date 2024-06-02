#include "PosOfWord.h"


int PosOfWord(FILE* input, Er *error, const char *word){
    int max = 1024;
    //int val = value(input);
    //printf("%d \n", val);
    char line[1024];
    int line_number = 0;
    int counter = 0;
    //line = (char*)malloc(max * sizeof(line));

    while (fgets(line, sizeof(line), input)) {
        
        line_number++;
        char *pos = line;
        int position = 0;
        
        while ((pos = strstr(pos, word)) != NULL) {
            position = pos - line;
            printf("Строка %d Позиция %d\n", line_number, position + 2); 
            pos = pos + 1;
            counter++;
        }
    }
    *error = OK;
    
    return counter;
}

