#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define error -1
#define SIZE (sizeof(unsigned int)*8)



int shislo_b_dv(unsigned  umber);
unsigned int inverse(int number, int i, int j);

unsigned int  inverse(int number, int i, int j){
	unsigned int otv;
	int mask;
	printf("введите правую  границу i");
	scanf("%d", &i);
	printf("введите левую границу j");
	scanf("%d", &j);
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

int shislo_b_dv(unsigned int number){
	for (int k = SIZE -1 ; k >= 0; k--){
		if ((1 << k) & number){
			printf("%d", 1);
		}else{
			printf("%d", 0);
		}
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
	scanf("%d", &number);

	answer = inverse( number, i, j);
	if (answer != error){

		printf(" число %d: %u\n",  number, answer);
		printf("%d  ", number);
		shislo_b_dv(number);
		printf("%u  ", answer);
		shislo_b_dv(answer);
		return 0;
	}
}


