#include <stdio.h>
#include <stdlib.h>

int reverse_array(double *Array, int len);
//Функция перезаписывает массив в обратном порядке. 

int reverse_array(double *Array, int len){

	int m = len/2;
	double c;
	
	for (int i=0; i < m; ++i){
		c = Array[i];
		Array[i] = Array[len-i-1];
		Array[len-i-1] = c;
	}
	
	return 0;
}


int main(void){
	
	char input[50];
	FILE *f_in, *f_out; 
	int len = 0, main_return_code = 0;
	double *Array = NULL;
	
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
	
	Array = (double *)malloc(len*sizeof(double)); // В массив записываются значения из введенного файла.
	if (Array == NULL){
		printf("Оперативная память не выделена\n");
		main_return_code = -1;
		goto terminate;
	}

	
	for (int i=0; i < len; ++i){
		if (fscanf(f_in, "%lf", &Array[i])!=1){
			printf("В файле недостаточкно значений\n");
			main_return_code = -1;
			goto terminate_1;
		}
	}
	
	reverse_array(Array, len);
		
	for (int i = 0; i < len; i++){  // В файл output.txt записываются значения из измененного массива.
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