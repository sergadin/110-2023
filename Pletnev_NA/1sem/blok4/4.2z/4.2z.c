#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE (sizeof(unsigned int) * 8)

int Mirror_Coup(unsigned int x);
int Bit_Len(unsigned int y);
void Print_Bit(unsigned int x, int n);

void Print_Bit(unsigned int x, int n)
{
	for (int k = n - 1; k >= 0; k--)
	{
		if ((k % 8) == 0)
		{
			printf("_");
		}

		if ((1 << k) & x)
		{
			printf("%d", 1);
		}
		else
		{
			printf("%d", 0);
		}
	}

	printf("\n");
}

int Bit_Len(unsigned int y)
{

	for (int k = SIZE - 1; k >= 0; k--)
	{
		if (((1 << k) & y) != 0)
		{
			return k + 1;
		}
	}
}

int Mirror_Coup(unsigned int x)
{
	int n = Bit_Len(x);
	bool e1;
	bool e2;

	for (int k = n - 1; k >= n / 2; k--)
	{
		e1 = ((1 << k) & x);
		e2 = ((1 << (n - 1 - k)) & x);

		x = (e2 << k) | (~(1 << k)) & x;
		x = (e1 << (n - 1 - k)) | (~(1 << n - 1 - k)) & x;
	}

	return x;
}

int main(void)
{
	unsigned int x;
	int n;

	printf("Enter the number:\n");
	scanf("%d", &x);

	n = Bit_Len(x);

	printf("Direct binary notation of a number (%d):\n", x);
	Print_Bit(x, n);

	printf("Reverse binary notation of a number: (%d):\n", x);
	Print_Bit(Mirror_Coup(x), n);

	return 0;
}
