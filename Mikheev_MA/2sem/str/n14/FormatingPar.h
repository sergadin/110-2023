#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum{
    OK,
    MEMORY
}Er;



void FormatingPar(FILE* input, FILE* output, Er *error, int wide);