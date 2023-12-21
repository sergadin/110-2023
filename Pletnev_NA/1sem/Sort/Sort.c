#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


void Generator_Array(int** main_arr, int len);
void Copy_Array(int* copy_arr, int* main_arr, int len);
void Time_Checks(FILE* out_f, int len);
void Bubble_P(int* a, int len);
int Validation_Сheck(int* a, int len);
int Quick_Bit_Sort_Partition(int* a, int n, int ibit);
bool Test_Bit(int x, int k);
int compare(const void* i, const void* j);
void swap(int* a, int* b);

// функция меняет значения двух переменных местами
void swap(int* a, int* b)
{
	int c = *a;
	*a = *b;
	*b = c;
}

// сравнение двух элементов на равенство(вспомог. функ. для qsort)
int compare(const void* i, const void* j)
{
	return (*(int*)i - *(int*)j);
}


//функция проверяет на корректнотсь работы сортировки
int Validation_Сheck(int* a, int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		if (a[i] > a[i + 1])
		{
			return 0;
		}
	}

	return 1;
}


bool Test_Bit(int x, int k)
{
	return x & (1 << k);
}

//Сортировка целого массива группировкой с последовательным упорядочиванием битов
int Quick_Bit_Sort_Partition(int* a, int n, int ibit)
{
	int i, j;
	while (true) {
		for (i = 0; i < n && !Test_Bit(a[i], ibit); i++);
		for (j = n - 1; j >= 0 && Test_Bit(a[j], ibit); j--);
		if (i == n || j == -1) return 0;
		if (i < j) {
			swap(a + i, a + j);
			++i, --j;
		}
		else {
			return j + 1;
		}
	}
}


//Сортировка просеиванием
void Bubble_P(int* a, int len)
{
	int i;
	int j;
	int t;
	int flagsort = 0;

	while (!flagsort)
	{
		flagsort = 1;
		for (i = 0; i < len - 1; ++i)
		{
			if (a[i] > a[i + 1])
			{
				t = a[i];
				a[i] = a[i + 1];
				a[i + 1] = t;
				j = i;

				while (j > 0 && !(a[j - 1] <= a[j]))
				{
					t = a[j];
					a[j] = a[j - 1];
					a[j - 1] = t;
					--j;
				}
				flagsort = 0;
			}
		}
	}
	return;
}


//функция создает случайный массив данных заддной длинны
void Generator_Array(int** main_arr, int len)
{
	*main_arr = (int*)malloc((len + 1) * sizeof(int));

	if ((*main_arr) == NULL)
	{
		return;
	}

	srand(time(NULL));

	for (int i = 0; i < len; i++)
	{
		(*main_arr)[i] = (int)(rand());
	}

}


//функция копирует созданный ранний массив
void Copy_Array(int* copy_arr, int* main_arr, int len)
{
	if (copy_arr == NULL)
	{
		printf("Error: RAM is not allocated\n");
		return;
	}

	for (int i = 0; i < len; i++)
	{
		copy_arr[i] = main_arr[i];
	}
	return;
}


//функция записывает время работы в сортировки в указанный файл
void Time_Checks(FILE* out_f, int len)
{

	int* main_arr = NULL;
	int* copy_arr = NULL;

	double st_time;
	double end_time;
	double r_time;

	main_arr = (int*)malloc((len + 1) * sizeof(int));
	copy_arr = (int*)malloc((len + 1) * sizeof(int));

	Generator_Array(&main_arr, len);

	fprintf(out_f, "Len = %d\n", len);

	Copy_Array(copy_arr, main_arr, len);
	st_time = clock();
	Bubble_P(copy_arr, len);
	end_time = clock();
	r_time = (double)(st_time - end_time);

	if (!(Validation_Сheck(copy_arr, len)))
	{
		fprintf(out_f, "- screening - sorting error\n");
	}
	else
	{
		fprintf(out_f, "- screening - time: %lf mc\n", r_time);
	}

	Copy_Array(copy_arr, main_arr, len);
	st_time = clock();
	for (int i = 0; i < len; i++)
	{
		Quick_Bit_Sort_Partition(copy_arr, len, i);
	}
	end_time = clock();
	r_time = (double)(st_time - end_time);

	if (!(Validation_Сheck(copy_arr, len)))
	{
		fprintf(out_f, "- bit - sorting error\n");
	}
	else
	{
		fprintf(out_f, "- bit - time: %lf mc\n", r_time);
	}

	Copy_Array(copy_arr, main_arr, len);
	st_time = clock();
	qsort(copy_arr, len, sizeof(int), compare);
	r_time = (double)(st_time - end_time);

	if (!(Validation_Сheck(copy_arr, len)))
	{
		fprintf(out_f, "- qsort - sorting error\n");
	}
	else
	{
		fprintf(out_f, "- qsort - time: %lf mc\n", r_time);
	}

	fprintf(out_f, "\n");

	free(main_arr);
	free(copy_arr);

	return;
}



int main(void)
{
	FILE* out_f;
	char fo[30];

	int len;
	int n = 1;

	printf("Enter the name of the output file:\n");
	scanf("%s", fo);

	out_f = fopen(fo, "w");

	printf("Enter the length of the random array:\n");
	scanf("%d", &len);

	for (int k = 1; k != 5; k++)
	{
		Time_Checks(out_f, n * len);
		n *= 2;
	}

	fclose(out_f);

	return 0;

}