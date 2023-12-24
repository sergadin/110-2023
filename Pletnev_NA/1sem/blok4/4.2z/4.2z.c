#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void Mirror_Coup(int x);

void Mirror_Coup(int x)
{
	int n = ceil(log2(x+1));

	printf("Mirror inverted broken representation of the number (%d):\n", x);

	for (int k = 0; k < n; k++)
	{
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
