#include <math.h>
#include "gauss_method.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct
{  /* структура для теста */
	const char* file_name; //название файла, в котором находятся элементы матрицы
	double* res; //ожидаемый результат
	Error err; //адрес ошибки
} Test;

int main(void)
{
	double* res;
	int n, m; //порядок матрицы - считывается из файла
	double* matr = NULL; //указатель на массив, содержащий элементы матрицы
	FILE* f = NULL;
	Error err;
	Test tests[] = { {"test1.txt", (double[]) { 1000 }, OK},
		{"test2.txt", (double[]) { 1.01315, 0.802631, -0.697368, 2.907894 }, OK},
		{"test3.txt", (double[]) { 0 }, NO_SOL},
		{"test4.txt", (double[]) { 0 }, NO_SOL},
		{"test5.txt", (double[]) { 0 }, SING_MATR} };
	for (int i = 0; i < 5; i++)
	{
		f = fopen(tests[i].file_name, "r");

		if (f == NULL)
		{								/*Открытие файла, считывание из него значений элементов матрицы и запись их в массив.*/
			printf("Тест %d не пройден. Ошибка чтения файла\n", i + 1);
			err = FILE_ER;
			goto end;
		}

		if (fscanf_s(f, "%d%d", &m, &n) != 2)
		{
			printf("Тест %d не пройден. Ошибка чтения файла\n", i + 1);
			err = FILE_ER;
			fclose(f);
			goto end;

		}

		matr = (double*)malloc((m * n) * sizeof(double));
		if (matr == NULL)
		{
			printf("Оперативная память не выделена\n");
			err = MEM_ER;
			fclose(f);
			goto end;
		}
		for (int i = 0; i < (m * n); ++i)
		{
			if (fscanf_s(f, "%lf", &matr[i]) != 1)
			{
				printf("В файле недостаточно значений\n");
				err = FILE_ER;
				free(matr);
				fclose(f);
				goto end;
			}
		}
		fclose(f);
		res = gauss_method(matr, m, n, &err);
		free(matr);

	end:
		if (err != tests[i].err)
		{
			printf("Тест %d не пройден.\n", i + 1);
		}
		else
		{
			if (err == OK)
			{
				printf("Тест %d пройден. Решение системы уравнений: ", i + 1);
				for (int i = 0; i < n; i++)
				{
					printf("%lf ", res[i]);
				}
				printf("\n");
			}
			else
			{
				printf("Тест %d пройден\n", i + 1);
			}
		}
	}
}
