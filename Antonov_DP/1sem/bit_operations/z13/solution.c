#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int search_of_high_config(int check, int config, int quan_bit);

int search_of_high_config(int check, int config, int quan_bit)
{
	int i = 0, len = -1;
	unsigned int test = (1 & config), additional = 1;
	config = config >> 1;
	for (i = 1; i < quan_bit; i++)
	{
		test += ((1 << i) *(1 & config));
		config = config >> 1;
		additional = (additional << 1) + 1;
	}
	i = 1;
	while (check > 0)
	{
		if (test == (check & additional))
		{
			len = i;
		}
		i++;
		check = check >> 1;
	}
	return len;
}

int main(void)
{
	int config, quan_bit, answ = 0;
	unsigned int check;
	printf("введите через пробел целое число, в котором ищется заданная конфигурация, и целое число, в котором задана конфигурация: ");
	if (scanf("%u %d", &check, &config) != 2)
	{
		printf("числа заданы некорректно \n");
		return -1;
	}
	printf("введите натуральное количество первых битов числа, у которого мы берём конфигурацию: ");
	if ((scanf("%d", &quan_bit) != 1) || (quan_bit < 1) || ((config >> (quan_bit - 1))) == 0)
	{
		printf("число задано некорректно \n");
		return -1;
	}
	answ = search_of_high_config(check, config, quan_bit);
	if (answ == -1) 
	{
		printf("такая конфигурация не встречается в данном числе \n");
		return 0;
	}
	printf("начиная с %d-ого бита повторяется такая конфигурация \n", answ);
	return 0;
}
