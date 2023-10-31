#include <stdio.h>
#include <stdlib.h>

int sum_array_elem(double *Array, int len);

int sum_array_elem(double *Array, int len){

	double summa=0.;
	
	for (int i=0; i < len; ++i){
		summa += Array[i];
		Array[i] = summa;
	}
	
	return *Array;
}


int main(void){
	
	char input[50];
	FILE *f_in, *f_out; 
	int len = 0, correct = 1;
	
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
		
	}else{
	
		double *Array = (double *)malloc(len*sizeof(double));
		if (Array == NULL){
		
			printf("Оперативная память не выделена\n");
			fclose(f_in);
			fclose(f_out);
			return -1;
		}

		
		for (int i=0; i < len; ++i){
			if (fscanf(f_in, "%lf", &Array[i])!=1){
			
				correct = 0;
				break;
			}
		}
		
		if (correct==1){
		
			*Array = sum_array_elem(Array, len);
			
			for (int i = 0; i < len; i++){
			
				fprintf(f_out, "%lf\n", Array[i]);
			}
			
			printf("Ответ выведен в файл output.txt\n");
			
		}else{
		
			printf("В файле недостаточкно значений\n");
		}
		
	free(Array);
	
	}

	fclose(f_in);
	fclose(f_out);
	return 0;
}
