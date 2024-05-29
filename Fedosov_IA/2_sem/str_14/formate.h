#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum {
	OK,             //Ошибок нет
    INP,           //Неподходящий размер
    OUTP,
}Error;


int formate(const char* filenameA, const char* fout, int width, Error *error);

/*
Функция форматирует абзацы текста в заданных границах.

Переменные: 
    1) filenameA - имя входного файлв
    2) fout - имя выходного файла
    3) width - длина строки отформатированного абзаца

Программа считывает строку и добавляет ее к абзацу, так получается строка абзаца, затем форматируется уже сам абзац.


*/