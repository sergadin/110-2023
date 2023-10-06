#include <stdio.h>
#include <math.h>
int main(void){
	FILE *f_in, *f_out;
	double c1,c2,c3,b;
	double a_n1=0.;
	double a_n0=0.;
	double curr;
	double epsilion;
	int flag=0;
	char file_input[30];
	
	printf("Введите имя входного файла: \n");
	scanf("%s", file_input);
	printf("Результат выводится в файл: output.txt.\n");
	f_in = fopen(file_input,"r");
	f_out = fopen("output.txt","w");
	printf("Введите значение погрешности: \n");
	scanf("%lf", & epsilion);
	printf("Введите коэффициент с1:\n");
	scanf("%lf", & c1);
	printf("Введите коэффициент с2:\n");
	scanf("%lf", & c2);
	printf("Введите коэффициент с3:\n");
	scanf ("%lf", & c3);
	printf("Введите значение b:\n");
	scanf ("%lf", & b);
	
	
	if ( f_in == NULL )
	{
		printf("Файл не открывается\n");
		return -1;
	}
	if (f_out == NULL){
		printf("Файл не открывается\n");
		return -1;	
	}
	if (fscanf(f_in, "%lf", & curr)!=1)
	{
		printf("ошибка чтения\n");
		return -1;
	}
	a_n1=a_n0;
	a_n0=curr;
	
	while (fscanf(f_in, "%lf", & curr)==1){
		if (flag>=1){
			if (fabs(((c1*a_n1)+(c2*a_n0)+(c3*curr))-b)>=epsilion){
				printf("Результат загружен в файл output.txt.\n");
				fprintf(f_out,"Последовательность не удовлетворяет условиям\n");
				fclose(f_in);
				fclose(f_out);
				return 0;
			}
			
			a_n1=a_n0;
			a_n0=curr;

		}else{
			flag+=1;
			a_n1=a_n0;
			a_n0=curr;
		}
	}
	if (flag==0){
		printf("В файле недостаточно значений.\n");
		fclose(f_in);
		fclose(f_out);
		return 0;
	}
	printf("Результат загружен в файл output.txt.\n");
	fprintf(f_out,"Последовательность удовлетворяет условиям\n");		
	fclose(f_in);
	fclose(f_out);
	return 0;
} 
