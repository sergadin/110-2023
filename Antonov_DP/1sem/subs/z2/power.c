#include <stdio.h>

double root (double num, int root);
double power (double num, int pow);

double power (double num, int pow)
{
	double answ = num;
	int i;
	for ( i = 1; i < pow; i += 1)
	{
		answ *= num;
	}
	return answ;
}

double root (double num, int root)
{
	double right = num, left = 0;
	int i;
	for ( i = 0; right - left >0.00001; i += 1)
	{
		if (power ((right + left) / 2, root) < num){
			left = (right + left) / 2;
		}
		else
		{
			right = (right + left) / 2;
		}
	}
	return right;
}
