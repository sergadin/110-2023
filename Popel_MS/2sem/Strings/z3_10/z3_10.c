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
 * Функция удаляет все элементы, сожержащиеся между "скобками" - элементами /* и //*. Если для правой границы нет пары,
 *                                                             элементы не удаляются. "Скобки" ведут себя так же, как и комментарии в Си.
 */
int Delete_sub_str(FILE *f, FILE* fout, Error *err){
    size_t len = 0;
    int size = 0, i = 0, have_frst_brd = 0;/*размер текущей строки, текущий индекс, индикатор наличия не парной левой скобки*/
    char *lft_board = "/*", *rgt_board = "*/", *istr1, *istr2, *buf = NULL; /*левая скобок, правая скобок, адреса позиций элементов, 
                                                                                                   совпавших с границами скобок.*/
    
    
    
    *err = NA_OK;
    
    while((getline(&buf, &len, f))!=-1){
        int not_write = 0;
        istr1 = strstr(buf, lft_board);
        istr2 = strstr(buf, rgt_board);
        if (have_frst_brd == 1){
            if (istr2 == NULL){
                memmove(buf, buf + size - 1, size);
                not_write = 1;
            }else{
                have_frst_brd = 0;
                memmove(buf, istr2 + 2, size - (istr2 - buf));
            }
        }

        while (istr1 != NULL){
            size = strlen(buf);
            if (istr2 == NULL){
                have_frst_brd = 1;
                memmove(istr1, buf + size - 1, size - (istr1 - buf));
            }else{
                memmove(istr1, istr2 + 2, size - (istr2 - buf));
            }
            istr1 = strstr(buf, lft_board);
            istr2 = strstr(buf, rgt_board);
        }

        if (not_write == 0){
        fprintf(fout, "%s", buf);
        }
        i++;
    }
	free(buf);
    return 0;
}
