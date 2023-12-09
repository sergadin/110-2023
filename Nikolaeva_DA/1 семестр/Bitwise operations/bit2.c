#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define SIZE (sizeof(unsigned int)*8)


//Эта функция переводит число в 2 систему счисления
int shislo_b_dv(unsigned number);
unsigned int inverse(int number);

unsigned int  inverse( int number){
        unsigned int otv;

        otv =~number;
        return otv;
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
	int number=0;
        unsigned int answer;
        
        printf("Введите целое число:\n");
        scanf("%d", &number);
    
       answer = inverse( number);
	
		
	printf(" число %d: %u\n",  number, answer);
            printf("%d  ", number);
            shislo_b_dv(number);
            printf("%u  ", answer);
            shislo_b_dv(answer);

	return 0;
}
	
