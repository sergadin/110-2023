#include <stdio.h>
#include <math.h>

int solution(FILE *f_in , FILE *f_out){

	double c1 , c2 , c3 , b , curr , epsilion;
	double a_n1 = 0.;
	double a_n0 = 0.;
	int sequence_corr = 0; //счетчик элементов и индикатор корректности последоватедьности
	
	printf("Введите значение погрешности: \n");
	scanf("%lf" , & epsilion);
	printf("Введите коэффициент с1:\n");
	scanf("%lf" , & c1);
	printf("Введите коэффициент с2:\n");
	scanf("%lf" , & c2);
	printf("Введите коэффициент с3:\n");
	scanf ("%lf" , & c3);
	printf("Введите значение b:\n");
	scanf ("%lf" , & b);
	
	if (fscanf(f_in, "%lf", & curr) != 1)
	{
		printf("ошибка чтения\n");
		return -1;
	}
	
	a_n1 = a_n0;
	a_n0 = curr;
	
	while (fscanf(f_in , "%lf" , & curr)==1){ 
		if (sequence_corr >= 1){
			if (fabs(((c1 * a_n1) + (c2 * a_n0) + (c3 * curr)) - b) >= epsilion){
				sequence_corr = -1;
			}
			
			a_n1 = a_n0;
			a_n0 = curr;
			if (sequence_corr != -1){
			sequence_corr += 1;
			}

		}else{
			if (sequence_corr != -1){
				sequence_corr += 1;
			}
			a_n1 = a_n0;
			a_n0 = curr;
		}
	}
	
	if ((sequence_corr == 1) || (sequence_corr == 0)){
		printf("В файле недостаточно значений.\n");
		return -1;
	}
	
	if (sequence_corr == -1){
		printf("Результат загружен в файл output.txt.\n");
		fprintf(f_out , "Последовательность не удовлетворяет условиям.\n");
		return 0;
	}
	
	printf("Результат загружен в файл output.txt.\n");
	fprintf(f_out,"Последовательность удовлетворяет условиям\n");
	
	return 0;
}

int main(void){
	FILE *f_in, *f_out;
	char file_input[30];
	
	printf("Введите имя входного файла: \n");
	scanf("%s" , file_input);
	printf("Результат выводится в файл: output.txt.\n");
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
	
	solution(f_in, f_out);
			
	fclose(f_in);
	fclose(f_out);
	return 0;
} 
