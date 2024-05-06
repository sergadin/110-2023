#include <math.h>
#include "z3_10.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{  /* новая переменаая-структура для проведения теста */
    const char * file_name; //название файла, содержащего редактируемая строка.
    Error err; //адрес ошибки
} TestCase;


int main(void){
	FILE *fout, *f;
	Error err; 
	int line = 1, res = 0; //количество строк, результат
	size_t len = 1024; 
	char **strs = NULL, *buf = NULL; //массив строк, текущая строка

    	err = NA_OK;
    	TestCase tests[] = {{"str2.txt", NA_OK},
		{"str3.txt", NA_OK},
		{"str1.txt", NA_OK},
    		{"str4.txt", NA_OK}};
	
	int n_tasks = sizeof(tests) / sizeof(tests[0]); /* количество тестов */
	for (int n = 0; n < n_tasks; n++){

		f = fopen(tests[n].file_name, "r");
		if (f == NULL){
			printf("Файл не открывается\n");
			err = FILE_WR;
			goto terminate;
		}
		buf = (char*)malloc(1024 * sizeof(char));
		if (buf == NULL){
			printf("Оперативная память не выделена\n");
			err = NA_MEMORY_ERR;
			fclose(f);
			goto terminate;
			}

		if (getline(&buf, &len, f) == -1){
			err = FILE_WR;
			fclose(f);
			free(buf);
			goto terminate;
		}
		while(!feof(f)){
			line++;
			getline(&buf, &len, f);
    		}
		free(buf);
    		rewind(f);

		strs = (char **)calloc(line, sizeof(char*));
		if (strs == NULL){
			printf("Оперативная память не выделена\n");
			err = NA_MEMORY_ERR;
			fclose(f);
			goto terminate;
			}

		fout = fopen("str_correct.txt", "w");

		if (fout == NULL){
			printf("Файл не открывается\n");
			err = FILE_WR;
			free(strs);
			fclose(f);
			goto terminate;
		}
	
			res = Delete_sub_str(strs, f, fout, line, &err);
			fclose(f);
			fclose(fout);
			terminate:
			
			if(err != tests[n].err){
				printf("Тест №%d не пройден.\n", n + 1);
			}else if(err == NA_OK){
				printf("Тест №%d пройден. Измененная строка записана в файл str_correct.txt\n", n + 1);
			}else{
				printf("Тест №%d успешно пройден.\n", n + 1);
			}
	}	
	return 0;	
}
