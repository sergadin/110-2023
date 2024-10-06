#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum {
	OK,             // ошибок нет
	FILE_ERR,       // проблемы с открытием файлов
}error;


void find_diff(const char* file_A, const char* file_B, const char* file_out, error *err);

/*
 * Функция находит строки, которые были удалены или добавлены из файла А в файл В, и записывает это в файл out
 * 
 * входные данные:
 *    file_A    - имя файла А
 *    file_B    - имя файла В
 *    file_out  - имя файла, в который записываем ответ
 *    err       - код ошибки
 */
