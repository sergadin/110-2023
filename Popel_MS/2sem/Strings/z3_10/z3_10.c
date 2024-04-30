#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "z3_10.h"


/*	Параметры: *filename - название файля, содержащего строку.
 *         *fout - адрес файла, содержащего строку
 *          size_s - длина строки
 *         *err - указатель на код ошибки.
 * Функция удаляет все элементы, сожержащиеся между "скобками" - парой любых элементой из словаря. Если для элемента из словаря нет пары,
 *                                                                                                             элементы не удаляются.
 */
int Delete_sub_str(const char *filename, FILE *fout, int size_s, Error *err){
    char *dict = ".,:;!&()/[]"; //Словарь элементов, части строки между которыми надо удалить.
    char *strs = malloc(size_s*sizeof(char)); //строка из переданного файла
    FILE *fstr = NULL;
    int size_d = strlen(dict), first_pos,  first = 1, i = 0; /*размер словаря, позиция первого элемента из словаря, индекс наличия "первого 
    элемента" из словаря (1, если еще не найден первый элемент, 0 - если найден), порядковый индекс*/
    fstr = fopen(filename, "r");
    if (fstr == NULL){
		printf("Файл не открывается\n");
		*err = FILE_WR;
		return -1;
	}
    if (fscanf(fstr, "%s", strs) != 1){
        printf("В файле недостаточно значений\n");
        *err = FILE_WR;
        return -1;
    }
    if (strs == NULL){
		printf("Оперативная память не выделена\n");
		*err = NA_MEMORY_ERR;
		return -1;
	}
    fclose(fstr);
    printf("\nИсходная строка - %s", strs);
    while (i < size_s){
        for (int j = 0; j<size_d;j++){
        
            if ((strs[i] == dict[j]) && first){
                first_pos = i;
                first = 0;
            }else if (strs[i] == dict[j]){
                first = 1;
                memmove(strs + first_pos, strs+i+1, size_s - i + 1);
                i = first_pos - 1;
            }
        }
        i++;
    } 
    printf("\nИсправленная строка - %s\n\n", strs);
    fprintf(fout, "%s\n", strs);
    free(strs);
    return 0;

}
