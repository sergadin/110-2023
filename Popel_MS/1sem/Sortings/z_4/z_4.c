#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Corr_ord 0
#define Uncorr_ord -1

int sort_insert(double *Array1, int len); //Функция сортирует массив методом вставок в неубывающем порядке.
					//Также замеряется время работы этой функции, и оно же выводится на экран при успешном завершении программы.
int ordered_seq(double *Array1, int len); //Функция проверяет итоговый массив на упорядоченность.
int random_array(double *Array_rand, int len_n);//Функция записывает массив случайных действительных значений 
                                               //(размер этого массива считывается с клавиатуры.)

int sort_insert( double *Array1, int len){
	double ins_val = 0.;
	 
	for (int i = 0; i< len-1; i++){
		
		ins_val = Array1[i+1];
		int j = i;

		while ((j >= 0) && (Array1[j] > ins_val)){
			
			Array1[j+1] = Array1[j];
			j--;
		}
		
		Array1[j+1] = ins_val;
	}
	
	return 0;
}

int ordered_seq(double *Array1, int len){
	double last_val = Array1[0];
	for (int i = 1; i < len; i++){
		if (last_val > Array1[i]){
			return Uncorr_ord;
		}
		last_val = Array1[i];
	}
	return Corr_ord;
}

int random_array(double *Array_rand, int len_n){
	
	srand(time(NULL));
	
	for (int i=0; i < len_n; i++){
		Array_rand[i] = rand()*0.01;
	}
	return 0;
}

int main(void){
	char input[50];
	clock_t start, end;
	double *Array1 = NULL, *Array_rand = NULL, seconds;
	FILE *f_in, *f_out; 
	int len = 0, order1 = 0, order2 = 0, len_n, main_return_code = 0;
	
	printf("Введите имя входного файла: \n");
	scanf("%s" , input);
	
	printf("Введите длину случайного массива: \n");
	scanf("%d", &len_n);
	
	f_in = fopen(input , "r");
	
	if (f_in == NULL){
	
		printf("Файл не открывается\n");
		return -1;
	}
	
	f_out = fopen("output.txt", "w");
	
	if (f_out == NULL){
	
		printf("Файл не открывается\n");
		fclose(f_in);
		return -1;
	}
	
	if (fscanf(f_in, "%d", &len)!=1){
		printf("Файл пуст\n");
		main_return_code = -1;
		goto terminate;
		
	}
	
	Array1 = (double *)malloc(len*sizeof(double));
	if (Array1 == NULL){
		printf("Оперативная память не выделена\n");
		main_return_code = -1;
		goto terminate_1;
	}

	
	for (int i = 0; i < len; ++i){
		if (fscanf(f_in, "%lf", &Array1[i])!=1){
			printf("В файле недостаточно значений\n");
			main_return_code = -1;
			goto terminate_1;
		}
	}
	
	start = clock();
	sort_insert( Array1, len);
	end = clock();
	seconds = (double)(end-start);
	order1 = ordered_seq(Array1, len);
	
	Array_rand = (double *)malloc(len_n*sizeof(double));
	if (Array_rand == NULL){
		printf("Оперативная память не выделена\n");
		goto terminate_1;
	}
	
	if (random_array( Array_rand, len_n) == -1){
		goto terminate_1;	
	}
	
	sort_insert(Array_rand, len_n);
	order2 = ordered_seq(Array_rand, len_n);
	
	if ((order1 == Uncorr_ord) || (order2 == Uncorr_ord)){
		printf("Последовательности не упорядочены\n");
		goto terminate_2;
	}else{
		printf("Последовательности упорядочены по неубыванию\n");
	}
	
	for (int i = 0; i< len; i++){
		fprintf(f_out, "%lf\n", Array1[i]);
	}
	fprintf(f_out, "%s\n", "\nRandom\n");
	for (int i = 0; i<len_n; i++){
		fprintf(f_out, "%lf\n", Array_rand[i]);
	}
	
	printf("Ответ выведен в файл output.txt\n");
	printf("Время выполнения алгоритма: %lf\n", seconds);
	
	terminate_2:
	
	free(Array_rand);
		
	terminate_1:

	free(Array1);
	
	terminate:
	
	fclose(f_in);
	fclose(f_out);
	return main_return_code;
}
