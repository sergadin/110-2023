#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

int Exponentiation(int x, int n);


int Exponentiation(int x, int n)
{
	int a0 = x*x;
	long long int a = 1;
	int len = ceil(log2(n + 1));
	int i;
	bool b;
	int t;

	b = ((1 << 0) & n);
	if (b == 1)
	{
		a *= x;
	}

	for (int k = 1; k < len; k++)
	{
		i = 1;
		b = ((1 << k) & n);
		t = k * b;

		while (i <= t)
		{
			a *= a0;
			i++;
		}
	}

	return a;
}



int main(void)
{
	int x;
	int n;
	long long int code;

	printf("Enter the number you want to raise:\n");
	scanf("%d", &x);

	printf("Enter the degree to which you want to raise:\n");
	scanf("%d", &n);

	code = Exponentiation(x, n);

	printf("%d^%d = %d\n", x, n, code);

	return 222;
}
