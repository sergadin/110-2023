#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "z3_13.h"


/*	Параметры: k - позиция, с которой начинается сравнение
 *         *buf - текущая строка 
 *         *str - итоговое слово
 * Функция ищет и записывает первое слово в данном фрагменте строки. Слово заканчивается, если встречается пробел, () или \n или заканчивается сама строка.
 */
static void check_word(long int k, char * buf, char *str);
static void check_word(long int k, char * buf, char *str){
    int have_word = -1, j = 0; /*индикатор наличия слов после слов-инструкций (-1 - нет, 0 - найдено хотя бы одно значение, 
    1 - окончание считывания), порядковый индекс*/
    for (int i = k; i < (strlen(buf) - 1); i++){
            if (((buf[i] == ' ') || (buf[i] == '(') || (buf[i]=='\n') || (i == (strlen(buf) - 2)) || (buf[i] == '\0')) && (have_word == 0)){
                have_word = 1;
                strncpy(str, buf + i - j, j);
            }
		    if ((buf[i] != ' ')&&(buf[i] != '\n')&&(buf[i] != '\0')&&(have_word < 1)){
                have_word = 0;
                j++;
		    }
        }
            
    }
        
        


/*	Параметры: *f - исходный файл.
 *         *fout - итоговый файл.
 *          line - количество строк в исходном файле.
 *         *err - указатель на код ошибки.
 * Функция обрабатывает текст полученного файла с кодом, сохраняя, в соответствии с выполнением условий, команды программы под инструкциями
 * #ifdef - #else - #endif. На вход подается рабочий код без синтаксических и логических ошибок (Если есть #ifdef или #else, то обязательно
 *                                                                                                                      прописан и #endif)
 */
int Condit_compil(FILE *f, FILE *fout, int line, Error *err){
    size_t len = 1024;
    ssize_t n_bytes = 0; //размер текущей строки
    int t = 0, k = 0, written = 0, if_ch = 0, el_ch = 0; /*количество найденных define, порядковый индекс, индикатор ввода строки в 
    итоговый файл (1 - не вводить, 0 - вводить), индикатор #ifdef - (-1 - удалить все после, 0 - не найден, 1 - найден, удалить только его),
                                                          индикатор #else - (аналогично)*/
    char define[] = "#define", *istr; /*строка #define, первый элемент текущего макроса в строке*/
    char hash1[] = "#ifdef", hash2[] = "#else", hash3[] = "#endif", *istr1,*istr2, *istr3; /*строки #ifdef, #else, #endif, индексы их 
                                                                                                                первых элементов*/
    char *str = NULL, *buf = NULL; //фрагмент текущей строки для сравнения, текущая строка.
    char ** str_arr = NULL; //словарь макросов после define



	
    *err = NA_OK;
    if (line == 0){
    	*err = FILE_WR;
    	return -1;
    }

    buf = (char *)calloc(sizeof(char), 1024);
    if (buf == NULL){
            printf("Оперативная память не выделена\n");
            *err = NA_MEMORY_ERR;
            return -1;
        }

    str_arr = (char **)calloc(sizeof(char*),line);
    if (str_arr == NULL){
            printf("Оперативная память не выделена\n");
            *err = NA_MEMORY_ERR;
            free(buf);
            return -1;
        }

    while ((n_bytes = getline(&buf, &len, f))!=-1){
        
        str_arr[k] = (char *)calloc(sizeof(char),n_bytes);
    	if (str_arr[k] == NULL){
            printf("Оперативная память не выделена%d - 1\n", k);
            printf("%ld - mem\n", n_bytes);
            *err = NA_MEMORY_ERR;
		for (int j = 0; j < k; j++){
		    	free(str_arr[j]);
		    }
		    free(str_arr);
            free(buf);
            return -1;
        }

    	str = (char *)calloc(sizeof(char),n_bytes);
    	if (str == NULL){
            printf("Оперативная память не выделена%d - 2\n", k);
            *err = NA_MEMORY_ERR;
		for (int i = 0; i < k; i++){
		    	free(str_arr[i]);
		    }
            free(buf);
		    free(str_arr);
            return -1;
        } 

      written = 0;
        istr = strstr(buf, define);

        if (istr != NULL){
            printf("Seeked word on position - %ld. Line - %d\n", istr - buf, k + 1);
            check_word(istr - buf + strlen(define), buf, str_arr[t]);
            t++;
        }	
            istr1 = strstr(buf, hash1);
            if(istr1 != NULL){
                printf("Seeked condition_1 on position - %ld. Line - %d\n", istr1 - buf, k+1);
                check_word(istr1 - buf + strlen(hash1), buf, str);
                if_ch = -1;
                for (int p = 0;  < t; p++){
                	if (strcmp(str_arr[p], str) == 0){
	                        if_ch = 1;
                    }
                }
                
                written = 1;
            }

            istr2 = strstr(buf, hash2);
            if (istr2 != NULL){
                printf("Seeked condition_2 on position - %ld. Line - %d\n", istr2 - buf, k + 1);
                if (if_ch == 1){
                    el_ch = -1;
                }else if (if_ch == -1){
                    el_ch = 1;
                    
                }
                if_ch = 0;
                written = 1;
            }

            istr3 = strstr(buf, hash3);
            if (istr3 != NULL){
                printf("Seeked condition_3 on position - %ld. Line - %d\n", istr3 - buf, k + 1);
                el_ch = 0;
                if_ch = 0;
                written = 1;
            }

        if ((el_ch == -1)||(if_ch == -1)){
            written = 1;
        }
        if (written == 0){
		fprintf(fout, "%s", buf);
        }

        free(str);
        k++;
    }

    for (int i = 0; i < line; i++){
    	free(str_arr[i]);
    }
    
    free(str_arr);
    free(buf);
    return 0;
}
