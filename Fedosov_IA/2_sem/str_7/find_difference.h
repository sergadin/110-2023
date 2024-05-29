#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum {
	OK,             //Ошибок нет
    INP,
    OUTP,
}Error;


int find_difference(const char* filenameA, const char* filenameB, const char* fout, Error *error);
/*
Функция находит строки которые были удалены или добавлены из файла А в файл В и записывает это в файл fout

Переменные:
    1)filenameA - имя файла А
    2)filenameB - имя файла В
    3)fout - имя выходного файла

Функция создает массив из строк файла А и массив из строк файла В, далее идет по элементам массива, то есть строкам, и сравнивает 
их, в зависимости от резальтата записывает их в добавленные или удаленные слова.
*/