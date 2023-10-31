#include <stdio.h>

double solution(FILE *f_in , FILE *f_out){

	double polinom = 0;
	double derivative = 0;
	double summa = 0;
	double x;
	double b = 0.;
	double a = 0.;
	
	printf("Введите значение переменной х: \n");
	scanf("%lf", & x);
	
	if (fscanf(f_in , "%lf", & b)!=1){
		printf("Ошибка чтения\n");
		return -1;
	}		
	polinom += b;
	while (fscanf(f_in , "%lf" , & a)==1){
		polinom *= x;
		polinom += a;
		derivative *= x;
		derivative += ( summa + b );
		summa = ( summa + b ) * x;
		b = a;
	}
	
	printf("Ответ загружен в файл 'output.txt'.\n");
	fprintf( f_out , "Значение выражения = %lf\n Значение производной выражения = %lf\n" , polinom , derivative);
	return 0;
}

int main(void){

	char file_input[30];
	double ans1 , ans2;
	FILE *f_in, *f_out;

	printf("Введите имя входного файла\n");
	scanf("%s" , file_input);
	f_in = fopen(file_input , "r");
	f_out = fopen("output.txt" , "w");

	if (f_in == NULL){
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
