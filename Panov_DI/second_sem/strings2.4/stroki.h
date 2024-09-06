#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {
	SUCCESS,          // Успех
	LONG_WORD,        // Длинное слово
	MEMORY_FAIL       // Ошибка выделения памяти
}error_t;


void split_long_lines(FILE* input, FILE* output, size_t max_length, error_t* err);


/*
** Функция убирает лишние подряд идущие символы, которые изначально заданы в
** словаре.
*/

