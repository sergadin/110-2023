#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int symmetric_num(int *answ, int l, int r);
int int_bin(int n, int *b);
int bin_in_int(int *b, int end, int st);

int bin_in_int(int *b, int end, int st)
{
	int i, summ = 0, j = 1;
	for (i = st; i != end; i = i + ((end - st) / abs(end - st)))
	{
		summ = summ + (b[i] * j);
		j = j * 2;
	}
	return summ;
}

int symmetric_num(int *answ, int l, int r)
{
	int i, p, len = 0;
	for (i = l; i < (r + 1); i++)
	{
		for (p = 0; (int)(i / (int)pow((double)2, (double) p)) != 0; p++) {}
		p = p - 1;
		if (((i % (int)pow(2, ((int)(p / 2)))) & ((int)(i % (int)pow(2, ((int)((p - 1) / 2)))))) == 0)
		{
			answ[len] = i;
			len++;
		}
	}
	return len;
}
int main(void)
{
	int l, r, i, len;
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
	len = symmetric_num(answ, l, r);
	for (i = 0; i < len; i++)
	{
		printf("%d\n", answ[i]);
	}
	l = 1 & ~(2);
	printf("%d", l);
	free(answ);
	return 0;
}
