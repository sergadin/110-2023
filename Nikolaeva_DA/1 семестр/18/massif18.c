#include <stdio.h>
#include <stdlib.h>

FILE* data;

void binomikoef(int *array, int N);


void binomikoef(int *array, int N){
	int k;
	array[0] = 1;
	for( k = 1; k <= N; ++k){
		int pred = 0;
		for (int i = 0; i <= k; ++i) {
			if (i < k) {// array[i] = array[i-1] + array[i]
		           int star = array[i];// запоминаем предыдующее значение
			   array[i] += pred;
			   pred = star;
			} 
			else{
				array[i] = pred;
			}
		}
	}
}
int main(void){
	int n;
	FILE *answer;
	int *array = NULL;
	answer = fopen("output.txt", "w");

	if (!answer) {     //Проверка существует ли answer
		printf("What?");
		return -1;
	}

	data = fopen("np1.txt", "r");

	if (!data) {     //Проверка есть ли data
		printf("ERR");
		return -1;
	}



	if (fscanf(data, "%d", &n)!=1){//Проверяем, считалось ли число
		printf("no values\n");
		return -1;
	}
	array = (int *)malloc((n+1)*sizeof(int));
	binomikoef(array, n);
	for (int i = 0; i <= n; ++i){
		fprintf(answer,"%d\n", array[i]);
	}

	fclose(data);
	free(array);
	fclose(answer);
	return 0;
}
