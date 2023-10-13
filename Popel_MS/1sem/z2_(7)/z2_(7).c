#include <stdio.h>
#include <math.h>

int solution(FILE *f_in , FILE *f_out){
	double epsilion;
	double curr;
	double min_c , max_c;
	int flag=0 , fl=0;
	
	printf("Введите значение погрешности: \n");
	scanf("%lf", & epsilion);
	
	
	if (fscanf(f_in, "%lf", & curr)!=1)
	{
		printf("ошибка чтения\n");
		return -1;
	}
	
	min_c = curr;
	max_c = curr;
	
	while(fscanf(f_in , "%lf" , & curr) == 1){   

		if (curr > max_c){
			max_c = curr;
		}
		if (curr < min_c){
			min_c = curr;
		}
	}
	
	printf("Результат загружен в файл output.txt.\n");
	
	if (fabs(min_c - max_c) >= epsilion){
		fprintf(f_out , "Значения не равны друг другу.\n");
	} else {
		fprintf(f_out , "Все значения равны друг другу с точностью до погрешности.\n");
	}
	
	return 0;
}

int main(void){

	char file_input[30];
	FILE *f_in , *f_out;
	
	printf("Введите имя входного файла: \n");
	scanf("%s" , file_input);
	f_in = fopen(file_input , "r");
	f_out = fopen("output.txt" , "w");
	
	if ( f_in == NULL )
	{
		printf("Файл не открывается\n");
		return -1;
	}
	if (f_out == NULL){
		printf("Файл не открывается\n");
		return -1;	
	}
	
	solution(f_in , f_out);
	
	fclose(f_in);
	fclose(f_out);
	return 0;
} 	
