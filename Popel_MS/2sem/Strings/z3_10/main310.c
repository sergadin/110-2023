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
	double res;
    FILE *fout;
	Error err;
    double temp;
    
    TestCase tests[] = {{"str2.txt", 3, NA_OK},
	{"str3.txt", 10, NA_OK},
	{"str1.txt", 15, NA_OK},
    {"str4.txt", 14, NA_OK}};
	
	int n_tasks = sizeof(tests) / sizeof(tests[0]); /* количество тестов */
	for (int n = 0; n < n_tasks; n++){
        fout = fopen("str_correct.txt", "w");
        if (fout == NULL){
            printf("Файл не открывается\n");
            return -1;
        }
	res = Delete_sub_str(tests[n].file_name, fout, tests[n].n, &err);
    fclose(fout);
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
