#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {
    OK,               // Все хорошо
    NO_SOLUTION,      // Система не определена
    SINGULAR_MATRIX,  // Матрица вырождена
    M_ALLOC_ERR       // Память не выделена
}error;


void copyWords(FILE* input, FILE* output, error* err);