#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define error -1
#define otr -2
#define out -5
#define No1 -3
#define No2 -4
#define SIZE (sizeof(unsigned int)*8)



int shislo_b_dv(unsigned int number);
int inverse(int number);

int  inverse(int number){
	int otv;
	int mask;
	int i;
	int j;
	printf("введите правую  границу i");
	if(scanf("%d", &i)!=1){
		printf(" Ошибка считывания\n" );
		return No1;
	}
	printf("введите левую границу j");
	if(scanf("%d", &j)!=1){
		printf("Ошибка считывания\n");
		return No2;
	}
	if(i<=0 || j<=0){
		printf("Отрицательное значение\n");
		return otr;
	}

	if(j > i){

		mask = ((1 << (j - i + 1)) - 1) << i;
		otv = number ^mask;

		return otv;
	}
	else{
		printf("Введены некоректные границы\n");
		return error;
	}
}

int shislo_b_dv( int unsigned number){
	for (int k = SIZE -1 ; k >= 0; k--){
		if ((1 << k) & number){
			printf("%d", 1);
		}else{
			printf("%d", 0);
		}
		if(k % 8 ==0)
			printf(" ");
	}
	printf("\n");
	return 0;
}


int main(void){
	int number = 0;
	int answer;
	int i;
	int j; 
	printf("Введите целое число:\n");
	if(scanf("%d", &number)!=1){
		printf("Плохое значение number");
		return out;
	}

	answer = inverse( number);
	if ((answer != error) && (answer != No1) && (answer != No2) && (answer != otr) && (answer != out)) {

		printf(" число %d: %u\n",  number, answer);
		printf("%d  ", number);
		shislo_b_dv(number);
		printf("%u  ", answer);
		shislo_b_dv(answer);
		return 0;
	}
}


