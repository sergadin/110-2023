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
	int i, len = 0, len_bin;
	int *num_bin;
	num_bin = (int *)malloc(8 * sizeof(int) * sizeof(int));
	for (i = l; i < (r + 1); i++)
	{
		len_bin = int_bin(i, num_bin);
		if (((bin_in_int(num_bin, (int)(len_bin / 2), 0)) == (bin_in_int(num_bin, (int)((len_bin - 1) / 2), len_bin - 1))) && (num_bin[0] == 1))
		{
			answ[len] = i;
			len++;
		}
	}
	free(num_bin);
	return len;
}
int int_bin(int n, int *b) 
{
	int mask = 1;
	int i;
	for (i = 0; mask; i++) 
	{
		if (n & mask) 
		{
			b[i] = 1;
		} 
		else 
		{
			b[i] = 0;
		}
		mask = mask << 1;
	}
	for (i = 31; (i > 0) && (b[i] == 0); i--) {}
	return (i + 1);
}

int main(void)
{
	int l, r, i, len;
	int *answ;
	printf("введите неотрицательные левую границу и првую границу диапозона через пробел: ");
	if ( scanf("%d %d", &l, &r) != 2)
	{
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
	free(answ);
	return 0;
}
