#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "z3_13.h"


/*	Параметры: k - позиция, с которой начинается сравнение
 *         *buf - текущая строка 
 *         *str - итоговое слово
 * Функция ищет и записывает первое слово в данном фрагменте строки. Слово заканчивается, если встречается пробел, () или \n.
 */
static void check_word(long int k, char * buf, char *str);
static void check_word(long int k, char * buf, char *str){
    int have_word = -1, j = 0; /*индикатор наличия слов после слов-инструкций (-1 - нет, 0 - найдено хотя бы одно значение, 
    1 - окончание считывания), порядковый индекс*/
    for (int i = k; i < (strlen(buf) - 1); i++){
            if (((buf[i] == ' ') || (buf[i] == '(') || (buf[i]=='\n') || (i == (strlen(buf) - 2))) && (have_word == 0)){
                have_word = 1;
                strncpy(str, buf + i - j, j);
            }
		    if ((buf[i] != ' ')&&(buf[i] != '\n')&&(have_word < 1)){
                have_word = 0;
                j++;
		    }
        }
            
    }
        
        


/*	Параметры: (*code_txt)[256] - массив строк с исходным текстом файла.
 *         (*answ_txt)[256] - массив, в который будет передан ответ. 
 *          line - количество строк в исходном файле.
 *         *err - указатель на код ошибки.
 * Функция обрабатывает текст полученного файла с кодом, сохраняя, в соответствии с выполнением условий, команды программы под инструкциями
 * #ifdef - #else - #endif. На вход подается рабочий код без синтаксических и логических ошибок (Если есть #ifdef или #else, то обязательно
 *                                                                                                                      прописан и #endif)
 */
int Condit_compil( char (*code_txt)[256], char (*answ_txt)[256], int line, Error *err){
    int t = 0, m = 0, /*len1=0, len2=0,*/ written = 0, if_ch = 0, el_ch = 0; /*количество define, количество сохраненных строк, индикатор ввода
    строки в итоговый файл (1 - не вводить, 0 - вводить), индикатор #ifdef - (-1 - удалить все после, 0 - не найден, 1 - найден, удалить только его),
                                                          индикатор #else - (аналогично)*/
    char define[] = "#define", *istr; /*строка #define, первый элемент текущего макроса в строке*/
    char hash1[] = "#ifdef", hash2[] = "#else", hash3[] = "#endif", *istr1,*istr2, *istr3; /*строки #ifdef, #else, #endif, индексы их первых 
    элементов*/
    char *str = NULL; //фрагмент текущей строки для сравнения.
    char ** str_arr = NULL; //словарь макросов после define
    *err = NA_OK;
    if (line == 0){
    	*err = FILE_WR;
    	return -1;
    }
    str_arr = (char **)malloc(sizeof(char*)*line);
    for (int i = 0; i < line; i++){
    	str_arr[i] = (char *)malloc(sizeof(char)*line);
    }
    for (int k = 0; k < line; k++){
    	str = (char *)malloc(sizeof(char)*256);
    	if (str == NULL){
            printf("Оперативная память не выделена\n");
            *err = NA_MEMORY_ERR;
            return -1;
        }
        //str[0] = '-'; 
        //printf("%ld - strlen, %s\n", strlen(str), str);

        written = 0;
        istr = strstr(code_txt[k], define);
        if (istr != NULL){
            printf("Seeked word on position - %ld. Line - %d\n", istr - code_txt[k], k + 1);
            check_word(istr - code_txt[k] + strlen(define), code_txt[k], str_arr[t]);
            t++;
        }
            istr1 = strstr(code_txt[k], hash1);
            if(istr1 != NULL){
                printf("Seeked condition_1 on position - %ld. Line - %d\n", istr1 - code_txt[k], k+1);
                check_word(istr1 - code_txt[k] + strlen(hash1), code_txt[k], str);
                if_ch = -1;
                for (int k = 0; k < t; k++){
                /*len1 = strlen(str);
                len2 = strlen(str_arr[k]);
                if (len1!=len2){
                	continue;
                }else{
                	for (int p = 0; p<len1; p++){
                		if (str_arr[k][p]!=str[p]){
                			if_ch = -1;
                			break;
                		}else{
                			if_ch = 1;
                		}
                	}
                }*/ 
			if (strcmp(str_arr[k], str) == 0){
	                        if_ch = 1;
                    }
                }
                
                written = 1;
            }
            istr2 = strstr(code_txt[k], hash2);
            if (istr2 != NULL){
                printf("Seeked condition_2 on position - %ld. Line - %d\n", istr2 - code_txt[k], k + 1);
                if (if_ch == 1){
                    el_ch = -1;
                }else if (if_ch == -1){
                    el_ch = 1;
                    
                }
                if_ch = 0;
                written = 1;
            }

            istr3 = strstr(code_txt[k], hash3);
            if (istr3 != NULL){
                printf("Seeked condition_3 on position - %ld. Line - %d\n", istr3 - code_txt[k], k + 1);
                el_ch = 0;
                if_ch = 0;
                written = 1;
            }
        if ((el_ch == -1)||(if_ch == -1)){
            written = 1;
       }
        if (written == 0){
        	strcpy(answ_txt[m], code_txt[k]);
        	m++;
        }
        free(str);
    }
   for (int i = 0; i < line; i++){
    	free(str_arr[i]);
    }
    free(str_arr);
    return m;
}
