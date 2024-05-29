#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
	OK,               // Все хорошо
	TOO_LONG_WORD,     // Записано слишком длинное слово
	M_ALLOC_ERR
}error;

void process_file(FILE* input, FILE* output, error* err);