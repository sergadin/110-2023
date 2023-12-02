#include <stdio.h>

int count(const char* name, double A, double e);
//Функция считывает количество вхождений A в файл с точностью до e
double fabs_(double a);


double fabs_(double a) {
	if (a < 0)
		return -a;
	else 
		return a;
}


int count(const char* name, double A, double e, FILE* data){
	double el;
	int cnt = 0;
	while (fscanf(data, "%lf", &el)==1){
		if (fabs_(el - A) <= e)
		      	cnt++;
	return cnt;
}


int main(void) {
	FILE *answer = fopen("output.txt", "w");
	FILE *data;
	char name[50];
	scanf("%s",name);
	data = fopen(name, "r");

	double x, e;
	scanf("%lf%lf", &x, &e);
	if (!answer) {
		printf("What?");
		return -1;
	}
	if (fprintf(answer, "%d", count("input.txt", x, e, data)) == 0) {
		printf("NO SUCCESS!!");
		return -2;
        	}
        if (!data)
                return -1;
	                 
        }
        if (!feof(data))
        {
                fclose(data);
                return -2;
        }
        fclose(data);


	fclose(answer);
	return 0;
}
