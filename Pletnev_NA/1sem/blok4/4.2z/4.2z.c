#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE (sizeof(unsigned int)*8) 

void Mirror_Coup(int x);
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




void Mirror_Coup(int x)
{
	int n = Bit_Len(x);

	printf("Direct binary notation of a number:\n", x);

	for (int k = n - 1; k >= 0; k--)
	{
		if ((1 << k) & x)
		{
			printf("%d", 1);
		}
		else
		{
			printf("%d", 0);
		}

		if ((k % 4) == 0)
		{
			printf("_");
		}
	}
	printf("\n");


	printf("Reverse binary notation of a number:\n", x);

	for (int k = 0; k < n; k++)
	{
		if ((k % 4) == 0)
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

	return;
}


int main(void)
{
	int x;

	printf("Enter the number:\n");
	scanf("%d", &x);

	Mirror_Coup(x);

	return 0;
}
