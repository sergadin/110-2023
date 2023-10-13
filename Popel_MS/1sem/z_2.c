#include <stdio.h>
#include <math.h>
int main(void){
	double epsilion;
	char file_input[30];
	char test[10000],t[10000];
	double curr;
	double min_c, max_c;
	int flag=0,fl=0;
	FILE *f_in, *f_out;
	
	printf("Введите имя входного файла: \n");
	scanf("%s", file_input);
	f_in = fopen(file_input,"r");
	f_out = fopen("output.txt","w");
	printf("Введите значение погрешности: \n");
	scanf("%lf", & epsilion);
	
	if ( f_in == NULL )
	{
		printf("Файл не открывается\n");
		return -1;
	}
	if (f_out == NULL){
		printf("Файл не открывается\n");
		return -1;	
	}
	fgets(test,10000,f_in);
	if (sscanf(test, "%lf", & curr)!=1)
	{
		printf("ошибка чтения\n");
		return -1;
	}
	min_c=curr;
	max_c=curr;
	while(fgets(test,10000,f_in)){
		if (sscanf(test, "%lf", & curr)!=1){
			if (sscanf(test, "%s", t)==1){
				printf("В файле содержатся некорректные значения.\n");
				fclose(f_in);
				fclose(f_out);
				return -1;
			}
			fl+=1;
			continue;
		}
		if (curr>max_c){
			max_c=curr;
		}
		if (curr<min_c){
			min_c=curr;
		}
		flag=1;
		if (fl!=0){
			printf("В файле содержатся некорректные значения.\n");
			fclose(f_in);
			fclose(f_out);
			return -1;	
		}
	}
	if (flag==0){
		printf("Файл пуст.\n");
		return -1;
	}
	printf("Результат загружен в файл output.txt.\n");
	if (fabs(min_c-max_c)>=epsilion){
		fprintf(f_out,"Значения не равны друг другу.\n");
	}else{
		fprintf(f_out,"Все значения равны друг другу с точностью до погрешности.\n");
	}
	fclose(f_in);
	fclose(f_out);
	return 0;
} 	
