#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define DIRECT_err -1
#define SIZE (sizeof(unsigned int)*8)-1
int direct;
//Эта функция делает циклический сдвиг битового представления числа вправо или влево (в зависимости от введенного в консоль значения)
//на указанное число элементов
int degree(unsigned num, int deg);
int count_rank_number(unsigned num);
int cycle_byte_shift( unsigned num, int swap);


int degree(unsigned num, int deg){
	int new_num = 1;
	for (int i = 0; i<deg; i++){
		new_num*=num;
	}
	return new_num;
}

int count_rank_number(unsigned num){
	int count = 0;
	int deb = num;
	while (deb > 0){
		deb /= 2;
		count += 1;
	}
	return count;
}

int cycle_byte_shift( unsigned num, int swap){
	int len = count_rank_number((unsigned) num);
	
	printf("Введите направление сдвига (введите '0, если влево' или '1, если вправо'): ");
	scanf("%d", &direct);
	if (direct!=1 && direct!=0){
		printf("Введено некорректное значение\n");
		return DIRECT_err;
	}
	
	if (direct == 0){
		return ((num & (degree(2, len)-1)) << swap) | ((num & degree(2,(SIZE-swap))) >> ((SIZE - swap)%(SIZE+1)));
	}else{
		return ((num & degree(2, swap)) >> swap) | ((num  & (degree(2, swap)-1))) << (((SIZE - swap)%(SIZE+1)));
	}
}

int main(void){
	int num;
	int swap;
	int answ;
	
	printf("Введите целое число:");
	scanf("%d", &num);
	
	printf("Введите сдвиг:");
	scanf("%d", &swap);
	
	answ = cycle_byte_shift((unsigned) num, swap);
	if (answ != DIRECT_err){
		if (direct == 0){
			printf("Вот сдвинутое влево на %d число %d: %d\n", swap, num, answ);
		}else{
			printf("Вот сдвинутое вправо на %d число %d: %d\n", swap, num, answ);
		}
		
	}
	return 0;
}
