#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "z3_13.h"


/*	Параметры: *top - указатель на следующий элемент.
 *         state - состояние строки - 1, 2 - если не надо удалять следующие строки, -1, -2 - если надо удалять следующие строки.
 * Функция записывает новое состояние и адрес следующего блока в стэке.
 */ 

OBJ* push(OBJ* top, int state);
OBJ* push(OBJ* top, int state){
    OBJ* ptr = malloc(sizeof(OBJ));
    ptr->state = state;
    ptr->next = top;
    return ptr;

}

/*	Параметры: *top - указатель на следующий элемент.
 * Функция удаляет указатель на следующий адрес, переходя к предыдущему блоку в стэке.
 */ 
OBJ* pop(OBJ* top);
OBJ* pop(OBJ* top){
    if(top == NULL){
        return top;
    }

    OBJ* ptr_next = top->next;
    free(top);
    return ptr_next;
}


/*	Параметры: 
 *          k - с какого момента начинать поиск (позиция последнего элемента найденного условия + 1)
 *          *buf - текущая строка.
 *          *str - строка, в которую будет записано найденное слово. 
 * Функция ищет первое слово, начиная с переданного индекса. 
 */

static void find_word(long int k, char * buf, char *str);
static void find_word(long int k, char * buf, char *str){
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
       

/*	Параметры: *str - текущая строка.
 *         *cond - условие, которое нужно найти в текущей строке.
 * Функция проверяет наличие переданного условия в данной строке. Если такого слова нет, возвращается -1, иначе - позиция первого элемента
 */

static int find_cond(char* str, char* cond);        
static int find_cond(char* str, char* cond){
    int len = strlen(str), corr = 0, j = 1, pos = 0;

    if (len < strlen(cond)){
        return -1;
    }

    for (int i = 0; i < len; i++){
        if (j == strlen(cond)){
            if ((str[i] == ' ') || (str[i] == '\n') || (str[i] == '\0') || (i==len-2)){
                return pos;
            }
        }
        if ((str[i] != ' ') && (corr != 1) && (str[i] != '#')){
            return -1;
        }else if ((corr == 0) && (str[i] == '#')){
            corr = 1;
            pos = i;
            continue;
        }
        if (corr == 1){
            if (str[i] == cond[j]){
                j++;
            }else{
                return -1;
            }
        }       
    }
    return pos;
}          


/*	Параметры: *f - массив строк с исходным текстом файла.
 *          *fout - массив, в который будет передан ответ. 
 *          line - количество строк в исходном файле.
 *         *err - указатель на код ошибки.
 * Функция обрабатывает текст полученного файла с кодом, сохраняя, в соответствии с выполнением условий, команды программы под инструкциями
 * #ifdef - #else - #endif. На вход подается рабочий код без синтаксических и логических ошибок (Если есть #ifdef или #else, то обязательно
 *                                                                                                                      прописан и #endif)
 */
int Condit_compil(FILE *f, FILE *fout, int line, Error *err){
    size_t len = 1024;
    OBJ* states = NULL; //первый блок стэка
    ssize_t n_bytes = 0; //количество элементов в текущей строке
    int def_numb = 0, k = 0, written = 0, if_ch = 0, el_ch = 0, def_pos = 0, if_pos = 0, else_pos = 0, endif_pos = 0; /*количество define, 
    количество сохраненных строк, индикатор ввода строки в итоговый файл (1 - не вводить, 0 - вводить), 
    индикатор #ifdef - (-1 - удалить все после, 0 - не найден, 1 - найден, удалить только его), индикатор #else - (аналогично),
    позиция первого элемента соответствующий слов-условий.*/
    char define[] = "#define"; /*строка #define, первый элемент текущего макроса в строке*/
    char ifdef_h[] = "#ifdef", else_h[] = "#else", endif_h[] = "#endif"; /*строки #ifdef, #else, #endif, индексы их первых элементов*/
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

    str_arr = (char **)calloc(sizeof(char*), line);
    if (str_arr == NULL){
            printf("Оперативная память не выделена\n");
            *err = NA_MEMORY_ERR;
            free(buf);
            return -1;
        }

    while ((n_bytes = getline(&buf, &len, f)) != -1){

    	str = (char *)calloc(sizeof(char),n_bytes);
    	if (str == NULL){
            printf("Оперативная память не выделена%d - 2\n", k);
            *err = NA_MEMORY_ERR;
            for (int i = 0; i < k; i++){
                    free(str_arr[i]);
            }
            free(buf);
            return -1;
        } 

        written = 0;

        if ((def_pos = find_cond(buf, define)) != -1){
            printf("Seeked word on position - %d. Line - %d\n", def_pos, k + 1);
            str_arr[def_numb] = (char *)calloc(sizeof(char), n_bytes);
            if (str_arr[def_numb] == NULL){
                printf("Оперативная память не выделена%d - 1\n", k);
                *err = NA_MEMORY_ERR;
                for (int j = 0; j < def_numb; j++){
                        free(str_arr[j]);
                    }
                    free(str_arr);
                    free(buf);
                    free(str);
                    return -1;
            }
            find_word(def_pos + strlen(define), buf, str_arr[def_numb]);
            def_numb++;
        }	

            else if((if_pos = find_cond(buf, ifdef_h)) != -1){
                printf("Seeked condition_1 on position - %d. Line - %d\n", if_pos, k + 1);
                find_word(if_pos + strlen(ifdef_h), buf, str);
                if_ch = -1;
                if ((states == NULL)||((states->state) >= 0)){
                    states = push(states, -1);
                    for (int p = 0; p < def_numb; p++){
                        if (strcmp(str_arr[p], str) == 0){
                                if_ch = 1;
                                states = pop(states);
                                states = push(states, 1);
                                break;
                        }
                    }
                }else{
                    states = push(states, -1);
                }
                written = 1;
            }

            else if ((else_pos = find_cond(buf, else_h)) != -1){
                printf("Seeked condition_2 on position - %d. Line - %d\n", else_pos, k + 1);
                if ((states->state) == 1){
                    el_ch = -1;
                    states = pop(states);
                    states = push(states, -2);
                }else if ((states->state) == -1){
                    el_ch = 1;
                    states = pop(states);
                    if (states!=NULL){
		            if((states->state)!=-1){
		                states = push(states, 2);
		            }else{
		                states = push(states, -1);
		                el_ch = -1;
		            }
                    }else{
                    	states = push(states, 2);
                    }
                }
                if_ch = 0;
                written = 1;
            }

            else if ((endif_pos = find_cond(buf, endif_h)) != -1){
                printf("Seeked condition_3 on position - %d. Line - %d\n", endif_pos, k + 1);
                states = pop(states);
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
    while(states != NULL){
        states = pop(states);
    }
    free(str_arr);
    free(buf);
    return 0;
}
