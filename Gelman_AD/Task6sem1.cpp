#include <stdio.h>
#include <stdlib.h>

int combinate_arrays(double* Array1, double* Array2, double* Array3, int len1, int len2);

int combinate_arrays(double* Array1, double* Array2, double* Array3, int len1, int len2) 
{

	int ind_1 = 0, ind_2 = 0;
	for (int i = 0; i < (len1 + len2); ++i) 
	{
		if ((ind_1 < len1) && ((ind_2 >= len2) || (Array1[ind_1] <= Array2[ind_2]))) 
		{
			Array3[i] = Array1[ind_1];
			ind_1 += 1;
		}
		else 
		{
			Array3[i] = Array2[ind_2];
			ind_2 += 1;
		}
	}

	return 0;
}

int main(void) 
{

	double* Array1 = NULL, * Array2 = NULL, * Array3 = NULL;
	char input[50];
	FILE* f_in, * f_out;
	int len1 = 0, len2 = 0, main_return_code = 0;

	printf("Введите имя входного файла: \n");
	scanf("%s", input);
	f_in = fopen(input, "r");

	if (f_in == NULL) 
	{
		printf("Файл не открывается\n");
		return -1;
	}

	f_out = fopen("output.txt", "w");

	if (f_out == NULL) 
	{
		printf("Файл не открывается\n");
		fclose(f_in);
		return -1;
	}

	if (fscanf(f_in, "%d%d", &len1, &len2) != 2) 
	{
		printf("Файл пуст\n");
		main_return_code = -1;
		goto terminate_1;

	}

	Array1 = (double*)malloc(len1 * sizeof(double));

	if (Array1 == NULL) 
	{
		printf("Оперативная память не выделена\n");
		main_return_code = -1;
		goto terminate_1;
	}

	Array2 = (double*)malloc(len2 * sizeof(double));

	if (Array2 == NULL) 
	{
		printf("Оперативная память не выделена\n");
		main_return_code = -1;
		goto terminate_2;
	}

	Array3 = (double*)malloc((len1 + len2) * sizeof(double));

	if (Array3 == NULL) 
	{
		printf("Оперативная память не выделена\n");
		main_return_code = -1;
		goto terminate_3;
	}

	for (int i = 0; i < len1; ++i) 
	{
		if (fscanf(f_in, "%lf", &Array1[i]) != 1) 
		{
			printf("В файле недостаточно значений либо значения не корректны\n");
			main_return_code = -1;
			goto terminate;
		}

		if (i >= 1) 
		{
			if (Array1[i] < Array1[i - 1]) 
			{
				printf("В файле значения не неубывают\n");
				main_return_code = -1;
				goto terminate;
			}
		}
	}

	for (int i = 0; i < len2; ++i) 
	{
		if (fscanf(f_in, "%lf", &Array2[i]) != 1) 
		{
			printf("В файле недостаточно значений либо значения не корректны\n");
			main_return_code = -1;
			goto terminate;
		}

		if (i >= 1) 
		{
			if (Array2[i] < Array2[i - 1]) 
			{
				printf("В файле значения не неубывают\n");
				main_return_code = -1;
				goto terminate;
			}
		}
	}

	combinate_arrays(Array1, Array2, Array3, len1, len2);

	for (int i = 0; i < (len1 + len2); i++) 
	{
		fprintf(f_out, "%lf\n", Array3[i]);

	}

	printf("Ответ выведен в файл output.txt\n");

	terminate:

	free(Array3);

	terminate_3:

	free(Array2);

	terminate_2:

	free(Array1);

	terminate_1:

	fclose(f_in);
	fclose(f_out);
	return main_return_code;
}