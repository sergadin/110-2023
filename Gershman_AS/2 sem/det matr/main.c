#include <math.h>
#include "z2_2.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct
{  /* структура для теста */
    const char * file_name; //название файла, в котором находятся элементы матрицы
	double res; //ожидаемый результат
	Error err; //адрес ошибки
} Test;

int main(void)
{
	double res = 0;
	int n = 0; //порядок матрицы - считывается из файла
	double *matr = NULL; //указатель на массив, содержащий элементы матрицы
	FILE *f = NULL;
	Error err;
	Test tests[] = {{"test1.txt", 1, OK}, {"test2.txt", 2, OK}, {"test3.txt", 0, ZER_MAT}, {"test4.txt", 0, OK}, {"test5.txt", -382.5, OK}};
    for (int i = 0; i < 5; i++)
	{
		f = fopen(tests[i].file_name, "r");

		if (f == NULL)
		{								/*Открытие файла, считывание из него значений элементов матрицы и запись их в массив.*/
			printf("Файл не открывается\n");
			err = FILE_ER;
			goto end;
		}

		if (fscanf(f, "%d", &n) != 1)
		{
			printf("Файл пуст\n");
			err = FILE_ER;
			fclose(f);
			goto end;
			
		}

		matr = (double *)malloc((n * n) * sizeof(double));
		if (matr == NULL)
		{
			printf("Оперативная память не выделена\n");
			err = MEM_ER;
			fclose(f);
			goto end;
		}
        for (int i = 0; i < (n * n); ++i)
		{   
			if (fscanf(f, "%lf", &matr[i])!=1)
			{
				printf("В файле недостаточно значений\n");
				err = FILE_ER;
				free(matr);
				fclose(f);
				goto end;
			}
		}
        fclose(f);
		res = determinate(matr, n, &err);
		free(matr);
		end:
        if(err != tests[i].err)
		{
			printf("Тест %d не пройден.\n", i + 1);
		}
        else
        {
            printf("Тест %d успешно пройден. Значение определителя матрицы: %lf\n", i + 1, res);
        }
    }
    return 0;
}

	
