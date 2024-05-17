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
    FILE *fout, *f;
	Error err;

    TestCase tests[] = {{"code1.c", NA_OK},
	{"code2.c", NA_OK},
	{"code3.c", NA_OK}};
	



	int n_tasks = sizeof(tests) / sizeof(tests[0]); /* количество тестов */

	for (int n = 0; n < n_tasks; n++){
		f = fopen(tests[n].file_name, "r");
		if (f == NULL){
			printf("Файл не открывается\n");
			err = FILE_WR;
			goto terminate;
		}

		fout = fopen("newcode.c", "w");

		if (fout == NULL){
			printf("Файл не открывается\n");
			err = FILE_WR;
			fclose(f);
			goto terminate;
		}

		Condit_compil(f, fout, &err);
		fclose(f);
		fclose(fout);

		terminate:
			if(err != tests[n].err){
				printf("Тест №%d не пройден.\n", n + 1);
			}else if(err == NA_OK){
				printf("Тест №%d пройден. Измененная строка записана в файл newcode.c\n", n + 1);
			}else{
				printf("Тест №%d успешно пройден.\n", n + 1);
			}		
	}	
	return 0;	
}
