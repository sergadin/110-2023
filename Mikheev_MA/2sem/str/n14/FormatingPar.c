#include "FormatingPar.h"


#define BUFFER_SIZE 1024


typedef enum{
    YES,
    NO
}TF; // TrueFalse


void PrintPar(FILE* output, int wide, char* paragraph);
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
            length_line = strlen("    ");
        }
        if(length_line + length_word > wide){
            length_line = 0;
            fprintf(output, "\n");
        }
        
        fprintf(output, "%s ", word);
        word = strtok(NULL, " \n");
        length_line = length_line + length_word;
        
    }
    
    fprintf(output, "\n");
}


void FormatingPar(FILE* input, FILE* output, Er *error, int wide){
    
    char full_text[BUFFER_SIZE];
    char paragraph[BUFFER_SIZE * 10] = "";
    TF isClearLine = YES;

    while(fgets(full_text, BUFFER_SIZE, input)){
        if(strcmp(full_text, "\n") == 0){
            
            if(isClearLine == YES){
                PrintPar(output, wide, paragraph);
                fprintf(output, "\n");  
                paragraph[0] = '\0';    
                isClearLine = YES;
            }
        }
        else{
            strcat(paragraph, full_text);
            isClearLine = YES;
        }
    }

    if(isClearLine == YES){
        PrintPar(output, wide, paragraph);
    }
    
}

