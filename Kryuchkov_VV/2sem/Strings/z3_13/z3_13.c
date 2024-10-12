#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "z3_13.h"


/*	Параметры: *top - указатель на следующий элемент.
 *         state - состояние строки - 1, 2 - если не надо удалять следующие строки, -1, -2 - если надо удалять следующие строки.
 * Функция записывает новое состояние и адрес следующего блока в стэке.
 */ 

OBJ* push(OBJ* top, int state);
OBJ* push(OBJ* top, int state)
{
    OBJ* ptr = malloc(sizeof(OBJ));
    ptr->state = state;
    ptr->next = top;
    return ptr;

}

/*	Параметры: *top - указатель на следующий элемент.
 * Функция удаляет указатель на следующий адрес, переходя к предыдущему блоку в стэке.
 */ 
OBJ* pop(OBJ* top);
OBJ* pop(OBJ* top)
{
    if(top == NULL)
    {
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
static void find_word(long int k, char * buf, char *str)
{
    char *white_space = " ";
    while(buf[k]==' ')
    {
   	    k++;
    }
    for (int i = k; buf[i] != 0; i++)
    {
        if(strchr(" (\r\n\t", buf[i]))
        {
            strncpy(str, buf + k, i - k);
            return;
        }
    }
}
       

/*	Параметры: *buf - текущая строка.
 *         *cond - условие, которое нужно найти в текущей строке.
 * Функция проверяет наличие переданного условия в данной строке. Если такого слова нет, возвращается -1, иначе - позиция первого элемента
 */

static int find_cond(char* buf, char* cond);        
static int find_cond(char* buf, char* cond)
{
	int i = 0, start = 0;
	char *white_space = " ";

   while(buf[i] == ' ')
   {
   	i++;
    }

    if (strlen(buf) < strlen(cond))
    {
    	return -1;
    }
    start = i;

    for (int k = 0; cond[k]; k++)
    {
    	if(cond[k] != buf[i])
        {
    		return -1;
    	}
    	i++;
    }

    if(strchr(" (\r\n\t", buf[i]) || buf[i] == '\0')
    {
    	return start;
    }
    return -1;
}          

/*	Параметры: *all_defines - указатель на следующий элемент.
 * Функция удаляет указатель на следующий адрес и указатель на текущее значение, переходя к предыдущему блоку в "массиве".
 */
static void do_undefine(struct item *all_defines);
static void do_undefine(struct item *all_defines)
{
    struct item *curr = all_defines->next;
    struct item *temp;
    while(curr != NULL){
    	temp = curr->next;
    	free(curr->term);
    	free(curr);
    	curr = temp;
    }
	printf("undefided\n");
}

/*	Параметры: *all_defines - указатель на текущий блок "массива".
 *         *term - проверяемое слово (строку).
 * Функция проверяет наличие переданного слова в "массиве" строк.
 */
static int is_defined(struct item *all_defines, char *term);
static int is_defined(struct item *all_defines, char *term){
    for(struct item *curr = all_defines->next; curr != NULL; curr = curr->next)
    {
        if(strcmp(curr->term, term) == 0)
        return -1;
    }
    return 0;
}

/*	Параметры: *all_defines - указатель на текущий блок "массива".
 *         *term - слово (строка).
 * Функция записывает в "массив" новое слово и создает следующий блок.
 */
static void register_define(struct item *all_defines, char *term);
static void register_define(struct item *all_defines, char *term){
    if (is_defined(all_defines, term))
    {
        return;
    }
    struct item *new_item = malloc(sizeof(struct item));
    new_item->next = all_defines->next;
    new_item->term = strdup(term);
    all_defines->next = new_item;
}

/*	Параметры: *f - массив строк с исходным текстом файла.
 *          *fout - массив, в который будет передан ответ. 
 *          line - количество строк в исходном файле.
 *         *err - указатель на код ошибки.
 * Функция обрабатывает текст полученного файла с кодом, сохраняя, в соответствии с выполнением условий, команды программы под инструкциями
 * #ifdef - #else - #endif. На вход подается рабочий код без синтаксических и логических ошибок (Если есть #ifdef или #else, то обязательно
 *                                                                                                                      прописан и #endif)
 */
int Condit_compil(FILE *f, FILE *fout, Error *err)
{
    size_t len = 0;
    OBJ* states = NULL; //первый блок стэка
    ssize_t n_bytes = 0; //количество элементов в текущей строке
    int k = 0, written = 0, if_ch = 0, el_ch = 0, def_pos = 0, if_pos = 0, else_pos = 0, endif_pos = 0; /*количество сохраненных строк, 
    индикатор ввода строки в итоговый файл (1 - не вводить, 0 - вводить), индикатор #ifdef - 
                            (-1 - удалить все после, 0 - не найден, 1 - найден, удалить только его), индикатор #else - (аналогично),
    позиция первого элемента соответствующий слов-условий.*/
    char define[] = "#define"; /*строка #define, первый элемент текущего макроса в строке*/
    char ifdef_h[] = "#ifdef", else_h[] = "#else", endif_h[] = "#endif"; /*строки #ifdef, #else, #endif, индексы их первых элементов*/
    char *str = NULL, *buf = NULL; //фрагмент текущей строки для сравнения, текущая строка.
    struct item all_defines = {NULL, NULL}; //первый блок "массива" слов.



    *err = NA_OK;

    buf = NULL;



    while ((n_bytes = getline(&buf, &len, f)) != -1)
    {
	
	str = (char *)calloc(sizeof(char),n_bytes);
    	if (str == NULL)
        {
            printf("Оперативная память не выделена%d - 2\n", k);
            *err = NA_MEMORY_ERR;
            free(buf);
            return -1;
        }

        written = 0;

        if ((def_pos = find_cond(buf, define)) != -1)
        {
            printf("Seeked word on position - %d. Line - %d\n", def_pos, k + 1);
            find_word(def_pos + strlen(define), buf, str);
            register_define(&all_defines, str);
        }	

            else if((if_pos = find_cond(buf, ifdef_h)) != -1)
            {
                printf("Seeked condition_1 on position - %d. Line - %d\n", if_pos, k + 1);
                find_word(if_pos + strlen(ifdef_h), buf, str);
                if_ch = -1;
                if ((states == NULL)||((states->state) >= 0))
                {
                    states = push(states, -1);
                    if (is_defined(&all_defines, str))
                    {
                        if_ch = 1;
                        states = pop(states);
                        states = push(states, 1);
                    }
                }
                else
                {
                    states = push(states, -1);
                }
                written = 1;
            }

            else if ((else_pos = find_cond(buf, else_h)) != -1)
            {
                printf("Seeked condition_2 on position - %d. Line - %d\n", else_pos, k + 1);
                if ((states->state) == 1)
                {
                    el_ch = -1;
                    states = pop(states);
                    states = push(states, -2);
                }
                else if ((states->state) == -1)
                {
                    el_ch = 1;
                    states = pop(states);
                    if (states!=NULL){
                        if((states->state) != -1)
                        {
                            states = push(states, 2);
                        }
                        else
                        {
                            states = push(states, -1);
                            el_ch = -1;
                        }
                    }
                    else
                    {
                        states = push(states, 2);
                    }
                }
                if_ch = 0;
                written = 1;
            }

            else if ((endif_pos = find_cond(buf, endif_h)) != -1)
            {
                printf("Seeked condition_3 on position - %d. Line - %d\n", endif_pos, k + 1);
                states = pop(states);
                el_ch = 0;
                if_ch = 0;
                written = 1;
            }

        if ((el_ch == -1)||(if_ch == -1))
        {
            written = 1;
        }
        if (written == 0)
        {
		    fprintf(fout, "%s", buf);
        }

	    free(str);
        k++;
    }

	do_undefine(&all_defines);

    while(states != NULL)
    {
        states = pop(states);
    }

    free(buf);
    return 0;
}
