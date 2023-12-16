#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define DIRECT_err -1
#define SIZE (sizeof(unsigned int)*8)
int direct;
//Эта функция делает циклический сдвиг битового представления числа вправо или влево (в зависимости от введенного в консоль значения)
//на указанное число элементов
unsigned int cycle_byte_shift( unsigned num, int swap);



int to_bin(unsigned int num){
  for (int k = SIZE -1 ; k>=0; k--){
    	if ((1 << k) & num){
    		printf("%d", 1);
    	}else{
    		printf("%d", 0);
    	}
    }
    printf("\n");

    return 0;
}

unsigned int cycle_byte_shift( unsigned num, int swap){
	
	printf("Введите направление сдвига (введите '0, если влево' или '1, если вправо'): ");
	scanf("%d", &direct);
	if (direct!=1 && direct!=0){
		printf("Введено некорректное значение\n");
		return DIRECT_err;
	}
	
	if (direct == 0){
		return ((num << swap) | (num >> (SIZE - swap)));
	}else{
		return ((num >> swap) | (num << (SIZE - swap)));
	}
}

int main(void){
	int num;
	int swap;
	int unsigned answ;
	
	printf("Введите целое число:");
	scanf("%d", &num);
	
	printf("Введите сдвиг:");
	scanf("%d", &swap);
	
	answ = cycle_byte_shift((unsigned) num, swap);
	if (answ != DIRECT_err){
		if (direct == 0){
			printf("Вот сдвинутое влево на %d число %d: %u\n", swap, num, answ);
	printf("%d - ", num);
            to_bin(num);
            printf("%u - ", answ);
            to_bin(answ);
		}else{
			printf("Вот сдвинутое вправо на %d число %d: %u\n", swap, num, answ);
		printf("%d - ", num);
            to_bin(num);
            printf("%u - ", answ);
            to_bin(answ);
		}
		
	}
	return 0;
}
