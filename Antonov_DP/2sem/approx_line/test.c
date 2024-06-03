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
	double *x, *y;
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
