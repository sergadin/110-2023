#include <math.h>
#include "z2_3.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct{  /* новая переменаая-структура для проведения теста */
    const char * file_name; //название файла, содержащего элементы матрицы
    int n; //порядок матрицы
	Error err; //адрес ошибки
} TestCase;



int main(void){
	double res, eps = 1e-5;
    FILE *fout;
	Error err;
    double temp;
    //double matr1[1] = {4}, matr2[4] = {1, 0.5, -9, 2}, matr3[9] = {1, 2, 3, 3, 2, 1, 4, 2, 5}, *matr4 = NULL;
   // double matr5[36] = {118, 146, 119, 140, 66, 142, 141, 75, 79, 76, 148, 3, 137, 51, 27, 23, 115, 110, 15, 126, 140, 36, 6, 56, 95, 20, 17, 124, 140, 94, 97, 131, 88, 148, 29, 36};
	
    TestCase tests[] = {{"matr1.txt", 1, NA_OK},
	{"matr2.txt", 2, NA_OK},
	{"matr3.txt", 3, NA_OK},
	{"matr4.txt", 0, NA_ZERO_MATR},
    {"matr5.txt", 6, NA_OK}};
	
	int n_tasks = sizeof(tests) / sizeof(tests[0]); /* количество тестов */
	for (int n = 0; n < n_tasks; n++){
        fout = fopen("inverse_matr.txt", "w");
        if (fout == NULL){
            printf("Файл не открывается\n");
            return -1;
        }
	res = Inverse_matr(tests[n].file_name, fout, tests[n].n, eps, &err);
        fclose(fout);
        fout = fopen("inverse_matr.txt", "r");
		if(err != tests[n].err){
			printf("Тест №%d не пройден.\n", n + 1);
		}else if(err == NA_OK){
			printf("Тест №%d пройден. Обратная матрица:\n\n", n + 1);
            for (int i = 0; i< (tests[n].n)*(tests[n].n); i++){
                fscanf(fout, "%lf", &temp);
                printf("%lf ", temp);
                if ((i+1)%(tests[n].n)==0){
                    printf("\n");
                }
            }
            printf("\n");
            fclose(fout);
		}else{
			printf("Тест №%d успешно пройден.\n", n + 1);
		}
	}
	return 0;	
}
