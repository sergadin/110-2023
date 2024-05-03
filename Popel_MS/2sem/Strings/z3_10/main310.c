#include <math.h>
#include "z3_10.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{  /* новая переменаая-структура для проведения теста */
    const char * file_name; //название файла, содержащего редактируемая строка.
    int n; //длина передаваемой строки
	Error err; //адрес ошибки
} TestCase;


int main(void){
	FILE *fout, *fstr;
	Error err;
	char *strs = NULL; //строка из переданного файла

    
    	TestCase tests[] = {{"str2.txt", 3, NA_OK},
	{"str3.txt", 10, NA_OK},
	{"str1.txt", 15, NA_OK},
    	{"str4.txt", 14, NA_OK}};
	
	int n_tasks = sizeof(tests) / sizeof(tests[0]); /* количество тестов */
	for (int n = 0; n < n_tasks; n++){

		strs = malloc(((tests[n].n) + 1)*sizeof(char));
		if (strs == NULL){
			printf("Оперативная память не выделена\n");
			err = NA_MEMORY_ERR;
			goto terminate;
		}

		fstr = fopen(tests[n].file_name, "r");
		if (fstr == NULL){
			printf("Файл не открывается\n");
			err = FILE_WR;
			free(strs);
			goto terminate;
		}

		if (fscanf(fstr, "%s", strs) != 1){
			printf("В файле недостаточно значений\n");
			err = FILE_WR;
			fclose(fstr);
			free(strs);
			goto terminate;
		}

		fclose(fstr);
	        fout = fopen("str_correct.txt", "w");
	
	        if (fout == NULL){
	            printf("Файл не открывается\n");
				free(strs);
	            goto terminate;
	        }
	
			Delete_sub_str(strs, tests[n].n, &err);
			fprintf(fout, "%s\n", strs);
			fclose(fout);
			terminate:
			
			if(err != tests[n].err){
				printf("Тест №%d не пройден.\n", n + 1);
			}else if(err == NA_OK){
				printf("Тест №%d пройден. Измененная строка записана в файл str_correct.txt\n", n + 1);
			}else{
				printf("Тест №%d успешно пройден.\n", n + 1);
			}
			free(strs);
		}	
	return 0;	
}
