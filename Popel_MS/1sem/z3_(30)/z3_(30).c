#include <stdio.h>
#define OK 0
#define NOT_OK -1


typedef struct {
	double pol;
	double der;
} Polyvalue;

int polinom_deriv(FILE *f_in, double x, Polyvalue *pv);

int polinom_deriv(FILE *f_in, double x, Polyvalue *pv){     //Программа считывает из файла коэффициенты многочлена по убыванию степеней. С клавиатуры считывается элемент х - относительно кот. подсчитывается значение многочлена и производной.

	double polinom = 0;
	double derivative = 0;
	double summa = 0;
	double coef1 = 0.;
	double coef2 = 0.;
	
	if (fscanf(f_in, "%lf", & coef2)!=1){
		return NOT_OK;
	}	
	
	polinom += coef2;
	
	while (fscanf(f_in, "%lf", & coef1)==1){
		polinom *= x;
		polinom += coef1;
		derivative *= x;
		derivative += (summa + coef2);
		summa = (summa + coef2) * x;
		coef2 = coef1;
	}

	pv->pol = polinom;
	pv->der = derivative;
	return OK;
}


int main(void){

	char file_input[30];
	double x;
	FILE *f_in, *f_out;
	Polyvalue pv;

	printf("Введите имя входного файла\n");
	scanf("%s", file_input);
	f_in = fopen(file_input, "r");
	f_out = fopen("output.txt", "w");

	if (f_in == NULL){
		 printf("Файл не открывается\n");
		 return -1;
	}

	if (f_out == NULL){
		printf("Файл не открывается\n");
		fclose(f_in);
		return -1;	
	}
	
	printf("Введите значение переменной х: \n");
	scanf("%lf", & x);
	
	if(polinom_deriv(f_in, x, & pv) == NOT_OK){
		printf("Ошибка чтения\n");
	}else{
		printf("Ответ загружен в файл 'output.txt'.\n");
		fprintf(f_out, "Значение выражения = %lf\n Значение производной выражения = %lf\n", pv.pol, pv.der);
	}
	
	fclose(f_in);
	fclose(f_out);			
	return 0;
}
