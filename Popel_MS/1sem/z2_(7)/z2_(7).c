#include <stdio.h>
#include <math.h>
#define NOT_OK -1
#define equal_val 0
#define not_equal_val -2

int equal_elem(FILE *f_in, double epsilion){ //Программа сравнивает все элементы последовательности. Если все элементы равны между собой
					    // с точностью до погрешности, программа удовлетворяет условиям, иначе - нет.
					   // Алгоритм: из файла считываются элементы, вычисляется минимальное и максимальное значение,
					  // значения сравниваются между собой с точностью до погрешности - результат будет ответом задачи.
	double curr;
	double min_c, max_c;
	
	if (fscanf(f_in, "%lf", & curr)!=1)
	{
		return NOT_OK;
	}
	
	min_c = curr;
	max_c = curr;
	
	while(fscanf(f_in , "%lf", & curr) == 1){   

		if (curr > max_c){
			max_c = curr;
		}
		if (curr < min_c){
			min_c = curr;
		}
	}
	
	if (fabs(min_c - max_c) >= epsilion){
		return not_equal_val;
	} else {
		return equal_val;
	}
}

int main(void){

	char file_input[30];
	double epsilion;
	int func_val;
	FILE *f_in, *f_out;
	
	printf("Введите имя входного файла: \n");
	scanf("%s", file_input);
	f_in = fopen(file_input, "r");
	f_out = fopen("output.txt", "w");
	
	if ( f_in == NULL )
	{
		printf("Файл не открывается\n");
		return -1;
	}
	if (f_out == NULL){
		printf("Файл не открывается\n");
		fclose(f_in);
		return -1;	
	}
	
	printf("Введите значение погрешности: \n");
	scanf("%lf", & epsilion);
	
	func_val = equal_elem(f_in, epsilion);
	
	if (func_val == NOT_OK){
		printf("ошибка чтения\n");
	}else{
		printf("Результат загружен в файл output.txt.\n");
		
		if (func_val == not_equal_val){
			fprintf(f_out, "Значения не равны друг другу.\n");
		}else{
			fprintf(f_out, "Все значения равны друг другу с точностью до погрешности.\n");
		}
	}
	fclose(f_in);
	fclose(f_out);
	return 0;
} 	
