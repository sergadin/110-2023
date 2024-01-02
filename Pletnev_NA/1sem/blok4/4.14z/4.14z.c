#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE (sizeof(unsigned int)*8) 

int Exponentiation(unsigned int x, unsigned int n);
int Bit_Len(unsigned int y);


int Bit_Len(unsigned int y)
{
	int d = 0;
	bool i;

	for (int k = SIZE - 1; k >= 0; k--)
	{
		i = ((1 << k) & y);
		if (i == 1)
		{
			d = k + 1;
			break;
		}
	}

	return d;
}


int Exponentiation(unsigned int x, unsigned int n)
{
	unsigned long long int a0 = x;
	unsigned long int a = 1;
	int len = Bit_Len(n);
	bool b;

	b = ((1 << 0) & n);
	if (b == 1)
	{
		a *= a0;
	}

	for (int k = 1; k < len; k++)
	{
		b = ((1 << k) & n);
		a0 *= a0;

		if (b == 1)
		{
			a *= a0;
		}
	}

	return a;
}



int main(void)
{
	unsigned int x;
	unsigned int n;
	unsigned int code;

	printf("Enter the number you want to raise:\n");
	scanf("%d", &x);

	printf("enter the degree to which you want to raise:\n");
	scanf("%d", &n);

	code = Exponentiation(x, n);

	printf("%d^%d = %d\n", x, n, code);

	return 222;
}
