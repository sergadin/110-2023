#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {
	SUCCESS,          // Успех
	LONG_WORD,        // Длинное слово
	MEMORY_FAIL       // Ошибка выделения памяти
}error_t;


void process_string(FILE* input, FILE* output, error_t* err);


/*
** Функция убирает лишние подряд идущие символы, которые изначально заданы в 
** словаре. 
*/

