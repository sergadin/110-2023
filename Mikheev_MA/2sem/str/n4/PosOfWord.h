#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum{
    OK,
    MEMORY
}Er;



int PosOfWord(FILE* input, Er *error, const char *word);