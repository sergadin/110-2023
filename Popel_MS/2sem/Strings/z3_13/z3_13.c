#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "z3_13.h"


/*	Параметры: i - позиция, с которой начинается сравнение
 *         *buf - текущая строка 
 *         *str - итоговое слово
 * Функция ищет и записывает первое слово в данном фрагменте строки. Слово заканчивается, если встречается пробел, () или \n.
 */
static char * check_word(int i, char * buf, char *str){
    int have_word = -1, j = 0; /*индикатор наличия слов после слов-инструкций (-1 - нет, 0 - найдено хотя бы одно значение, 
    1 - окончание считывания), порядковый индекс*/
    for (i; i < 256; i++){
            if (((buf[i] == ' ') || (buf[i] == '(') || (buf[i]=='\n')) && (have_word == 0)){
                have_word = 1;
                break;
            } 
            if ((buf[i] != ' ')&&(buf[i] != '\n')&&(have_word < 1)){
                str[j] = buf[i];
                j++;
                have_word = 0;
            
            }
        }
        
    return str;
}

/*	Параметры: *filename - имя файла, содержащего редактируемый код.
 *         *fout - адрес итогового файла. 
 *         *err - указатель на код ошибки.
 * Функция обрабатывает текст полученного файла с кодом, сохраняя, в соответствии с выполнением условий, команды программы под инструкциями
 * #ifdef - #else - #endif. На вход подается рабочий код без синтаксических и логических ошибок (Если есть #ifdef или #else, то обязательно
 *                                                                                                                      прописан и #endif)
 */
int Condit_compil(const char * filename, FILE * fout, Error *err){
    FILE *f;
    int t, count_of_def = 0, line = 1, written = 0, if_ch = 0, el_ch = 0; /*количество define, порядковый номер текущей строки, индикатор ввода
    строки в итоговый файл (1 - не вводить, 0 - вводить), индикатор #ifdef - (-1 - удалить все после, 0 - не найден, 1 - найден, удалить только его),
                                                          индикатор #else - (аналогично)*/
    char buffer[256], define[] = "#define", str_arr[256][256], *istr; /*текущая строка, строка #define, словарь макросов после define, первый 
    элемент текущего макроса в строке*/
    char hash1[] = "#ifdef", hash2[] = "#else", hash3[] = "#endif", *istr1,*istr2, *istr3, str[256]; /*строки #ifdef, #else, #endif, индексы их
    первых элементов, фрагмент текущей строки для сравнения.*/
    f = fopen(filename, "r+");
    if (f == NULL){
            printf("Файл не открывается\n");
            *err = FILE_WR;
            return -1;
        }
    while ((fgets(buffer, 256, f))!=NULL){
        written = 0;
        istr = strstr(buffer, define);
        if (istr == NULL){
        }else{
            printf("Seeked word on position - %ld. Line - %d\n", istr - buffer, line);
            check_word(istr - buffer + strlen(define), buffer, str_arr[t]);
        count_of_def++;
        }
            istr1 = strstr(buffer, hash1);
            if(istr1!=NULL){
                printf("Seeked condition1 on position - %ld. Line - %d\n", istr1 - buffer, line);
                check_word(istr1 - buffer + strlen(hash1), buffer, str);
                if_ch = -1;
                for (int k = 0; k < count_of_def; k++){
                    if (strcmp(str_arr[k], str) == 0){
                        if_ch = 1;
                        break;
                    }
                }
                written = 1;
            }
            istr2 = strstr(buffer, hash2);
            if (istr2 != NULL){
                printf("Seeked condition2 on position - %ld. Line - %d\n", istr2 - buffer, line);
                if (if_ch == 1){
                    el_ch = -1;
                }else if (if_ch == -1){
                    el_ch = 1;
                    if_ch = 0;
                }
                written = 1;
            }

            istr3 = strstr(buffer, hash3);
            if (istr3 != NULL){
                printf("Seeked condition3 on position - %ld. Line - %d\n", istr3 - buffer, line);
                el_ch = 0;
                if_ch = 0;
                written = 1;
            }
        if ((el_ch == -1)||(if_ch == -1)){
            written = 1;
       }
        if (written == 0){
            fprintf(fout, "%s", buffer);
        }
       line ++;
    }
    fclose(f);
    return 1;
}
