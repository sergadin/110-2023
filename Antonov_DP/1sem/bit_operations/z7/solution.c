#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int symmetric_numbers(int *answ, int l, int r);
int int_bin(int n, int *b);
int symmetric_num(unsigned int num);

int symmetric_num(unsigned int num)
{
	unsigned int test = 0;
	int i, j;
	test = -1;
	for (i = 32; (test & num) == num ; i--){ test = test >> 1;}
	i++;
	test = 0;
	for (j = 0; j < (int)(i / 2); j++)
	{
		test = (test << 1) + (1 & num);
		num = num >> 1;
	}
	if ((i % 2) == 1) {num = num >> 1;}
	if ((test - num) == 0) { return 1; }
	return 0;
}

int symmetric_numbers(int *answ, int l, int r)
{
	unsigned int i, len = 0;
	for (i = l; i < (r + 1); i++)
	{
		if (symmetric_num(i) == 1)
		{
			answ[len] = i;
			len++;
		}
	}
	return len;
}
int main(void)
{
	int l, r, i, len, j;
	int *answ;
	printf("введите неотрицательные левую границу и првую границу диапозона через пробел: ");
	if ( scanf("%d %d", &l, &r) != 2)
	{
	        printf("диапозон задан некорректно \n");
		return -1;
	}
	if ((l > r) || (l < 0) || (r < 0))
	{
		printf("диапозон задан некорректно \n");
		return -1;
	}
	answ = (int *)malloc(((int)((r - l) / 2)) * sizeof(int));
	len = symmetric_numbers(answ, l, r);
	for (i = 0; i < len; i++)
	{
		printf("%d ", answ[i]);
		for (j = 1; j < 32; j++)
		{
			if (j % 8 == 0)
			{
				printf("%d ", (answ[i] & 1));
				answ[i] = answ[i] >> 1;
			}
			printf("%d", (answ[i] & 1));
                        answ[i] = answ[i] >> 1;
		}
		printf("\n");
	}
	free(answ);
	return 0;
}
