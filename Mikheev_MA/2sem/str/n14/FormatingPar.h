#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum{
    OK,
    MEMORY
}Er;


/* Функция форматирует текст по заданной ширине по абзацам
** 
** На входе подается входной файл, выходной файл, код ошибки, максимальная
** ширина строки. Функция читает по абзацам(до пустых строк), форматирует
** их до нужной ширины, печатает.
*/
void FormatingPar(FILE* input, FILE* output, Er *error, int wide);