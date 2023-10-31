#include <stdio.h>
#include <stdlib.h>

int sum_array_elem(double *Array, int len);
//Функция перезаписывает массив по следующему принципу: 
//на i-ое место записывается сумма всех предыдущих элементов массива, включая значение i-ого элемента. 

int sum_array_elem(double *Array, int len){

	double summa=0.;
	
	for (int i=0; i < len; ++i){
		summa += Array[i];
		Array[i] = summa;
	}
	
	return 0;
}


int main(void){
	
	char input[50];
	FILE *f_in, *f_out; 
	int len = 0, main_return_code = 0;
	
	printf("Введите имя входного файла: \n");
	scanf("%s" , input);
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
	
	double *Array = (double *)malloc(len*sizeof(double)); 
	if (Array == NULL){
		printf("Оперативная память не выделена\n");
		main_return_code = -1;
		goto terminate_1;
	}

	
	for (int i=0; i < len; ++i){    //В созданный массив записываются элементы из входного файла
		if (fscanf(f_in, "%lf", &Array[i])!=1){
			printf("В файле недостаточкно значений\n");
			main_return_code = -1;
			goto terminate_1;
		}
	}
	
	sum_array_elem(Array, len);
		
	for (int i = 0; i < len; i++){   //Измененный массив записывается в файл output.txt
		fprintf(f_out, "%lf\n", Array[i]);
			
	}
		
	printf("Ответ выведен в файл output.txt\n");
		
	terminate_1:

	free(Array);
	
	terminate:
	
	fclose(f_in);
	fclose(f_out);
	return main_return_code;
}
