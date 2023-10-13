#include <stdio.h>
#include <string.h>
int main(void){
	double polinom = 0;
	double derivative = 0;
	char file_input[30];
	double summa = 0;
	double x;
	double b=0.;
	double a=0.;
	char test[100000];
	int flag=0, fl=0;
	
	FILE *f_in, *f_out;

	printf("Введите имя входного файла\n");
	scanf("%s", file_input);
	f_in = fopen(file_input, "r");
	f_out = fopen("output.txt","w");
	printf("Введите значение переменной х: \n");
	scanf("%lf", & x);

	if (f_in==NULL){
		 printf("Файл не открывается\n");
		 return -1;
	}

	if (f_out==NULL){
		printf("Файл не открывается\n");
		return -1;	
	}			
	fgets(test, 100000,f_in);
	if (sscanf(test, "%lf", & b)!=1){
		printf("Ошибка чтения\n");
		return -1;
	}		
	polinom += b;
	while (fgets(test, 100000, f_in)){
		if (sscanf(test, "%lf", &a)!=1){
			fl+=1;
			continue;
		}
		polinom*=x;
		polinom+=a;
		derivative*=x;
		derivative+=(summa+b);
		summa=(summa+b)*x;
		b=a;
		flag=1;
		if (fl!=0){
			printf("В файле содержатся некорректные значения или пустые строчки.\n");
			fclose(f_in);
			fclose(f_out);
			return -1;
		}
	}
	if (flag==0){
		printf("Файл пуст.\n");
		return -1;
		}
	printf("Ответ загружен в файл 'output.txt'.\n");		
	fprintf(f_out,"Значение выражения = %lf\n Значение производной выражения = %lf\n", polinom, derivative);
	fclose(f_in);
	fclose(f_out);
	return 0;
}
