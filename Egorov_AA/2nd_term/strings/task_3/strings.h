#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {
	OK,               // Все хорошо
	TOO_LONG_WORD,     // Записано слишком длинное слово
	M_ALLOC_ERR
}error;


void copyWords(FILE* input, FILE* output, error* err);


/*
** Функция копирования слов из input.txt в output.txt, причем каждое слово
** записывается в новой строчке.
**
** На вход функции подаются указатели на файл с входными значениями и на файл,
** куда записываются слова.
**
** Функция пробегает по всем символам из файла и смотрит: является ли оно знаком
** пунктуации или нужным нам словом. Если натыкается на знак пунктуации или пробел,
** то функция выписывает в новую строку слово до этого символа, если оно не повторялось
** до этого
**
** Важно: записанное слово не должно превышать в длину 512 символов. В противном
** случае программа работать не будет
**
** Если все прошло хорошо, в файле inputN.txt увидим выписанные слова.
*/

