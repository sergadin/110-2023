#include <stdio.h>

int get_max_index(unsigned int num); //функция для получения позиции, где стоит последняя единица в битовом представлении

unsigned int bit_reverse(unsigned int num, int index); //функция для зеркального отражения битового представления числа

int main() {
	unsigned int num;
	unsigned int reversed_num;
	int index;
	
	if (scanf("%u", &num) != 1) {
		printf("неверные входные данные\n");
		return -1;
	}
	
	index = get_max_index(num);	
	
	reversed_num = bit_reverse(num, index);
	
	printf("%u\n", reversed_num);
	
	return 0;
}


/*unsigned int bit_reverse(unsigned int num){
	unsigned int reversed_num = 0;
	unsigned int num_of_bits = sizeof(num) * 8;
	 
	for (int i = 0; i < num_of_bits; i++) {
		if ((num & (1 << i)) != 0) {
			reversed_num = reversed_num | (1 << ((num_of_bits - 1) - i)); 
		}
	}
	
	return reversed_num;
}
*/


int get_max_index(unsigned int num){
	int index;
	for (int i = 1; i < 33; i++) {
		if ((num & (1 << (32 - i))) != 0){
			index = 32 - i + 1;
			//printf("%d\n", index);
			return index;
		}
	}
}
	

unsigned int bit_reverse(unsigned int num, int index){
	unsigned int reversed_num = 0;
	//unsigned int num_of_bits = sizeof(num) * 8;
	 
	for (int i = 0; i < index; i++) {
		if ((num & (1 << i)) != 0) {
			reversed_num = reversed_num | (1 << ((index - 1) - i)); 
		}
	}
	
	return reversed_num;
}	





















