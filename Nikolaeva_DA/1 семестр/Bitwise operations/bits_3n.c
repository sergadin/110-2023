#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define OSHIBKA -1
#define SIZE (sizeof(unsigned int)*8)

//Эта функция делает циклический сдвиг битового представления числа вправо или влево 
unsigned int sdvig_k( unsigned number, int change);
//Эта функция переводит число в 2 систему счисления
int shislo_b_dv(unsigned number);





unsigned int sdvig_k( unsigned number, int change){
	int m;
	
	printf("Ввод направления сдвига направление сдвига: 0 если влево, 1 если в право): ");
	scanf("%d", &m);
	if (m!=1 && m!=0){
		printf("Введено некорректное значение\n");
		return OSHIBKA;
	}
	
	if (m == 0){
		return ((number << change)) | (number >> (SIZE - change));
	}else{
		return ((number >> change) | (number << (SIZE - change)));
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
	int number;
	int change;
	unsigned int answer;
	
	printf("Введите целое число:");
	scanf("%d", &number);
	
	printf("Введите сдвиг:");
	scanf("%d", &change);
    

	
	answer = sdvig_k((unsigned) number, change);
	if (answer != OSHIBKA){
		
			printf(" произведён сдвиг %d число %d: %u\n", change, number, answer);
            printf("%d  ", number);
            shislo_b_dv(number);
            printf("%u  ", answer);
            shislo_b_dv(answer);

		}

	return 0;
}
	

