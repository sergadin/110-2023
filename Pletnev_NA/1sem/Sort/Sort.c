#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


void Generator_Array(int** main_arr, int len);
void Copy_Array(int* copy_arr, int* main_arr, int len);
void Time_Checks(FILE* out_f, int len);
void Bubble_P(int* a, int len);
int Validation_Check(int* a, int len);
void Radius_Bit_Sort(int* arr, int n, int numBits);
int compare(const void* i, const void* j);


// сравнение двух элементов на равенство(вспомог. функ. для qsort)
int compare(const void* i, const void* j)
{
	return (*(int*)i - *(int*)j);
}


//функция проверяет на корректнотсь работы сортировки
int Validation_Check(int* a, int len)
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


//функция для получения значения бита на данной позиции
int getBit(int num, int pos) {
	return (num >> pos) & 1;
}


//Поразрядная битовая сортировка
void Radius_Bit_Sort(int* arr, int len, int numBits)
{
	const int BASE = 2; // Основание системы счисления (0 и 1)

	for (int bitPos = 0; bitPos < numBits; bitPos++)
	{
		int* output = (int*)(malloc((len+1)*sizeof(int)));
		int count[2] = {0};

		for (int i = 0; i < len; i++) 
		{
			count[getBit(arr[i], bitPos)]++;
		}

		for (int i = 1; i < BASE; i++) 
		{
			count[i] += count[i - 1];
		}

		for (int i = len - 1; i >= 0; i--) 
		{
			output[count[getBit(arr[i], bitPos)] - 1] = arr[i];
			count[getBit(arr[i], bitPos)]--;
		}

		for (int i = 0; i < len; i++) 
		{
			arr[i] = output[i];
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
	r_time = (double)(end_time - st_time);

	if (!(Validation_Check(copy_arr, len)))
	{
		fprintf(out_f, "- screening - sorting error\n");
	}
	else
	{
		fprintf(out_f, "- screening - time: %lf mc\n", r_time);
	}

	Copy_Array(copy_arr, main_arr, len);
	st_time = clock();
	Radius_Bit_Sort(copy_arr, len, 64);
	end_time = clock();
	r_time = (double)(end_time - st_time);

	if (!(Validation_Check(copy_arr, len)))
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
	r_time = (double)(end_time - st_time);

	if (!(Validation_Check(copy_arr, len)))
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