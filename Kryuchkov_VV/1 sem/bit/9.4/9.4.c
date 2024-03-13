#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE (sizeof(unsigned int)*8) 

int exp_rais(unsigned int x, unsigned int n);// Возводит в степень
int Len(unsigned int y); //Количество элементов


int Len (unsigned int y)
{
	int d = 0;
	bool k;
	for (int i = SIZE - 1; i >= 0; i--)
	{
		k = ((1 << i) & y);
		if (k == 1)
		{
			d = i + 1;
			break;
		}
	}
	return d;
}


int exp_rais(unsigned int x, unsigned int n)
{
	unsigned long long int a0 = x;
	unsigned long int a = 1;
	int len = Len(n);
	bool b;

	for (int i = 0; i < len; i++)
	{
		b = ((1 << i) & n);
		if (b == 1)
		{
			a = a * a0;
		}
		a0 = a0 * a0;
	}
	return a;
}



int main(void)
{
	unsigned int x;
	unsigned int n;
	unsigned int c;
	
	printf("Введите основание:\n");
  	scanf("%u", &x);

  	printf("Введите степень:\n");
  	scanf("%u", &n);
	
	c = exp_rais(x, n);

	printf("%d^%d = %d\n", x, n, c);

	return 0;
}
