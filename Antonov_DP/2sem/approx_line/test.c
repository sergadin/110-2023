#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "approx_line.h"


int main(void)
{
	ERR err = OK;
	double a, b, eps = 0.000001;
	int len;
	FILE *input, *output;
	double *x, *y, min, max;
	input = fopen("input.txt", "r");
	output = fopen("output.txt", "w");
	fscanf(input, "%d", &len);
	x = (double *)malloc(len * sizeof(double));
	y = (double *)malloc(len * sizeof(double));
	for (int i = 0; i < len; i++)
	{
		fscanf(input,"%lf %lf", &x[i], &y[i]);
	}
	err = OK;
	approx_line(x, y, &a, &b, len, eps, &err);
	fprintf(output, "set terminal dumb\n");
	min = x[0];
	max = x[0];
	for (int i = 0; i < len; i++)
	{
		if (min > x[i])
		{
			min = x[i];
		}
		if (min > y[i])
                {
                        min = y[i];
                }
		if (max < x[i])
                {
                        max = x[i];
                }
		if (max < y[i])
                {
                        max = y[i];
                }
	}
	min--;
	max++;
	fprintf(output, "set xrange [%lf : %lf]\n", min, max);
	fprintf(output, "set yrange [%lf : %lf]\n", min, max);
	fprintf(output, "plot (y = (%lf * x) + %lf), '-' with points \n", a, b);
	for (int i = 0; i < len; i++)
	{
		fprintf(output, "%lf %lf \n", x[i], y[i]);
	}
	fprintf(output, "e");
	free(x);
	free(y);
	fclose(input);
	fclose(output);
	return 0;
}
