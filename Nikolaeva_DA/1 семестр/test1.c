#clude <stdio.h>
#include <stdlib.h>
FILE* data;
int repl_amount( double *array, int N);  //Функция заменяет элемент на сумму предыдующих элементов


int repl_amount( double *array, int N){
	int i;
	for (i=1; i<N; i++){
		array[i]=array[i-1]+array[i];}
	
	return 0;
}
   int main(void){
	int n;
	FILE *answer;
	double *array = NULL;
        answer = fopen("output.txt", "w");

	if (!answer) {//Проверка существует ли answer
      		printf("What?");
      		return -1;
	}
        data = fopen("input1.txt", "r");

  	if (!data) {printf("ERR"); return -1;}//Проверка есть ли data
	if (fscanf(data, "%d", &n)!=1){//Проверяем, считалось ли число
		printf("no values\n");
		return -1;

	}
	array = (double *)malloc(n*sizeof(double));
	for (int i = 0; i<n; i++){
		if(fscanf(data, "%lf", &array[i]) != 1) {
			printf("FGH");
			return -1;
		
		}// считался ли элемент

	}

	for (int i =0; i<n;i++){
		printf("%lf\n",array[i]);

	}
	
	fclose(data);
	repl_amount(array, n);

	for (int i=0; i<n; i++){
		fprintf(answer, "%lf\n", array[i]);
	}
 
  	fclose(answer);
return 0;
   }
