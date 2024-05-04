#include <math.h>
#include "z3_13.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{  /* новая переменаая-структура для проведения теста */
    const char * file_name; //Название файла, содержащего редактируемый код
	Error err; //адрес ошибки
} TestCase;



int main(void){
	int i = 1, res = 0;
    FILE *fout, *f;
	Error err;
	char code_txt[256][256], answ_txt[256][256];
    TestCase tests[] = {{"code1.c", NA_OK},
	{"code2.c", NA_OK},
	{"code1.c", NA_OK}};
	
	int n_tasks = sizeof(tests) / sizeof(tests[0]); /* количество тестов */
	for (int n = 0; n < n_tasks; n++){
		i = 1;
		f = fopen(tests[n].file_name, "r");
		if (f == NULL){
            printf("Файл не открывается\n");
            err = FILE_WR;
            goto terminate;
        }
		if ((fgets(code_txt[0], 256, f)) == NULL){
			printf("Файл пуст\n");
			err = FILE_WR;
			fclose(f);
			goto terminate;
		}
		while((fgets(code_txt[i], 256, f)) != NULL){
			i++;
		}
		fclose(f);
		res = Condit_compil(code_txt, answ_txt, i, &err);
		fout = fopen("newcode.c", "w");
			if (fout == NULL){
				printf("Файл не открывается1\n");
				return -1;
			}
			terminate:
			if(err != tests[n].err){
				printf("Тест №%d не пройден.\n", n + 1);
			}else if(err == NA_OK){
				for (int j = 0; j < res; j++){
					fprintf(fout, "%s", answ_txt[j]);
				}
				fclose(fout);
				printf("Тест №%d пройден. Измененная строка записана в файл newcode.c\n", n + 1);
			}else{
				printf("Тест №%d успешно пройден.\n", n + 1);
			}
		
	}	
	return 0;	
}
