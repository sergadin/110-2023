#include <stdio.h>
#include <math.h>
#define Correct_seq 0
#define Err_reading -1
#define Not_enough_val -2
#define Uncorrect_seq -3


int sequence_cor(FILE *f_in, double c1, double c2, double c3, double b, double epsilion){

	double curr;
	double a_n1 = 0.;
	double a_n0 = 0.;
	int sequence_count = 0; //счетчик элементов и индикатор корректности последоватедьности
	
	if (fscanf(f_in, "%lf", & curr) != 1)
	{
		return Err_reading;
	}
	
	a_n1 = a_n0;
	a_n0 = curr;
	
	while (fscanf(f_in, "%lf", & curr)==1){ 
		if (sequence_count >= 1){
			if (fabs(((c1 * a_n1) + (c2 * a_n0) + (c3 * curr)) - b) >= epsilion){
				sequence_count = -1;
			}
			
			a_n1 = a_n0;
			a_n0 = curr;
			if (sequence_count != -1){
			sequence_count += 1;
			}

		}else{
			if (sequence_count != -1){
				sequence_count += 1;
			}
			a_n1 = a_n0;
			a_n0 = curr;
		}
	}
	
	if ((sequence_count == 1) || (sequence_count == 0)){
		return Not_enough_val;
	}
	
	if (sequence_count == -1){
		preturn Uncorrect_seq;
	}
		
	return Correct_seq;
}

int main(void){
	FILE *f_in, *f_out;
	char file_input[30];
	int func_val;
	double c1, c2, c3, b, epsilion;
	
	printf("Введите имя входного файла: \n");
	scanf("%s", file_input);
	printf("Результат выводится в файл: output.txt.\n");
	f_in = fopen(file_input, "r");
	f_out = fopen("output.txt", "w");
	
	
	
	if (f_in == NULL)
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
	printf("Введите коэффициент с1:\n");
	scanf("%lf", & c1);
	printf("Введите коэффициент с2:\n");
	scanf("%lf", & c2);
	printf("Введите коэффициент с3:\n");
	scanf("%lf", & c3);
	printf("Введите значение b:\n");
	scanf("%lf", & b);
	
	func_val = sequence_cor(f_in, c1, c2, c3, b, epsilion);
	if(func_val == Err_reading){
		printf("Ошибка чтения\n");
	}else if (func_val == Not_enough_val){
		printf("В файле недостаточно значений.\n");
	}else {
		printf("Результат загружен в файл output.txt.\n");
		if (func_val == Uncorrect_seq){
			fprintf(f_out, "Последовательность не удовлетворяет условиям.\n");
		}else{
			fprintf(f_out,"Последовательность удовлетворяет условиям\n");
		}
	}
			
	fclose(f_in);
	fclose(f_out);
	return 0;
} 
