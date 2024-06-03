#include "FormatingPar.h"


typedef enum{
    YES,
    NO
}TF; // TrueFalse


void PrintPar(FILE* output, int wide, char* paragraph); // печать абзаца
void PrintPar(FILE* output, int wide, char* paragraph){
    int length_line = 0;
    int length_word = 0;
    char *word;
    TF FirstLine = YES;
    
    word = strtok(paragraph, " \n");
    
    while(word != NULL){
        length_word = strlen(word);
        if(FirstLine == YES){
            FirstLine = NO;
            fprintf(output,"    ");
            //length_line = 4;
            length_line = strlen("    ");
        }
        if(length_line + length_word > wide){
            length_line = 0;
            fprintf(output, "\n");
        }
        
        fprintf(output, "%s ", word);
        word = strtok(NULL, " \n");
        length_line = length_line + length_word + 1;
        
    }
    
    fprintf(output, "\n");
}


void FormatingPar(FILE* input, FILE* output, Er *error, int wide){
    char *full_text;
    char *paragraph;
    TF isClearLine = YES;
    
    full_text = (char*)malloc(1024 * sizeof(char));
    if(full_text == NULL){
        *error = MEMORY;
        return;
    }
    
    size_t paragraph_size = 1024;
    paragraph = (char*)malloc(paragraph_size * sizeof(char));
    if(paragraph == NULL){
        free(full_text);
        *error = MEMORY;
        return;
    }
    
    paragraph[0] = '\0';

    while (fgets(full_text, 1024, input)){
        if (strcmp(full_text, "\n") == 0){
            if (isClearLine == YES){
                PrintPar(output, wide, paragraph);
                fprintf(output, "\n");
                paragraph[0] = '\0';
                isClearLine = YES;
            }
        }
        
        else{
            size_t new_length = strlen(paragraph) + strlen(full_text) + 1;
            if(new_length > paragraph_size){
                paragraph_size = paragraph_size * 2;
                paragraph = (char*)realloc(paragraph, paragraph_size * sizeof(char));
                if (paragraph == NULL) {
                    free(full_text);
                    *error = MEMORY;
                    return;
                }
            }
            strcat(paragraph, full_text);
            isClearLine = YES;
        }
    }

    if (isClearLine == YES && strlen(paragraph) > 0) {
        PrintPar(output, wide, paragraph);
    }

    free(full_text);
    free(paragraph);
}

