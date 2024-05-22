#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {
    OK,               // Все хорошо
    TOO_LONG_WORD     // Записано слишком длинное слово
}error;


void copyWords(FILE* input, FILE* output, error* err);
