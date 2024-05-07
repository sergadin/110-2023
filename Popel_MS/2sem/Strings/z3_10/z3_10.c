#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "z3_10.h"


/*	Параметры: **strs - Строка, переданная в программу.
 *          *f - исходный файл.
 *         *fout - итоговый файл.
 *         line - количество строк.
 *         *err - указатель на код ошибки.
 * Функция удаляет все элементы, сожержащиеся между "скобками" - элементами /* и *\/. Если для правой границы нет пары,
 *                                                             элементы не удаляются. "Скобки" ведут себя так же, как и комментарии в Си.
 */
int Delete_sub_str(char **strs, FILE *f, FILE* fout, int line, Error *err){
    size_t len = 1024;
    int size = 0; //размер текущей строки
    char *lft_board = "/*", *rgt_board = "*/", *istr1, *istr2; /*левая скобок, правая скобок, адреса позиций элементов, 
                                                                                                   совпавших с границами скобок.*/
    int i = 0, have_frst_brd = 0;/*текущий индекс, индикатор наличия не парной левой скобки*/
    
    *err = NA_OK;
    
    for (int j = 0; j < line; j++){
        strs[j] = (char*)calloc(sizeof(char),1024);
        if (strs[j] == NULL){
		printf("Оперативная память не выделена\n");
		*err = NA_MEMORY_ERR;
		for (int k = 0; k < j; k ++){
			free(strs[k]);
		}
	    return -1;
	}
    }

    while(!feof(f)){

        int not_write = 0;
        getline(&strs[i], &len, f);
        istr1 = strstr(strs[i], lft_board);
        istr2 = strstr(strs[i], rgt_board);
        if (have_frst_brd == 1){
            if (istr2 == NULL){
                memmove(strs[i], strs[i] + size - 1, size);
                not_write = 1;
            }else{
                have_frst_brd = 0;
                memmove(strs[i], istr2 + 2, size - (istr2 - strs[i]));
            }
        }

        while (istr1 != NULL){
            size = strlen(strs[i]);
            if (istr2 == NULL){
                have_frst_brd = 1;
                memmove(istr1, strs[i] + size - 1, size - (istr1 - strs[i]));
            }else{
                memmove(istr1, istr2 + 2, size - (istr2 - strs[i]));
            }
            istr1 = strstr(strs[i], lft_board);
            istr2 = strstr(strs[i], rgt_board);
        }

        if (not_write == 0){
            fprintf(fout, "%s", strs[i]);
        }
        i++;
    }

    for (int j = 0; j < line; j++){
        free(strs[j]);
    }

    free(strs);
    return 0;
}
