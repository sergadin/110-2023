#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int determin_position_of_point(double x, double y, double *coor_x, double *coor_y, int len);
int intersec_ray_segm(double x0, double y0, double a0, double b0, double x1, double y1, double a1, double b1);		//рассчитывает пересекает ли луч отрезок или нет
int point_belon_segm(double x0, double y0, double x1, double y1, double x2, double y2);

int point_belon_segm(double x0, double y0, double x1, double y1, double x2, double y2)
{
	if ((((x2 - x0) * (y1 - y0)) == ((y2 - y0) * (x1 - x0))) && (((0 < ((x2 - x0) * (x1 - x0))) && ((fabs(x1 - x0) - fabs(x2 - x0)) > 0)) || (fabs(x2 - x0) < 0.001)))
	{
		return 1;
	}
	return 0;
}

int intersec_ray_segm(double x0, double y0, double a0, double b0, double x1, double y1, double a1, double b1)
{
	double par0, par1, eps = 0.0001;	//par0 - параметр задающий луч, par1- параметр задающий отрезок, eps - малое число, для сравнения double
	if (fabs((a0 * b1) - (a1 * b0)) < eps)
	{
		return 0;
	}
	par1 = (b0 * (x0 - x1) - a0 * (y0 - y1)) / ((a1 * b0) - (a0 * b1));
	if (fabs(a0) < eps)
	{
		par0 = (y1 + b1 * par1 - y0) / b0;
	}
	else
	{
		par0 = (x1 + a1 * par1 - x0) / a0;
	}
	if ((0 < par1) && (par1 < 1) && (par0 > 0))
	{
		printf("%lf %lf \n", par0, par1);
		return 1;
	}
	return 0;
}

int determin_position_of_point(double x, double y, double *coor_x, double *coor_y, int len)
{
	int i, count = 1;	//count считает количество пересечений между многоугольником и лучом
	double a0, b0, eps = 0.0001;	//координаты направляющего вектора луча и eps - маленькое число
	a0 = ((coor_x[0] + coor_x[1]) / 2) - x;
	b0 = ((coor_y[0] + coor_y[1]) / 2) - y;
	if (point_belon_segm(coor_x[0], coor_y[0], coor_x[1], coor_y[1], x, y) == 1)
        {
        	return -1;
        }
	for (i = 2; i < len; i++)
	{
		if ((fabs(coor_x[i] - coor_x[i - 1]) > eps) && (fabs(coor_y[i] - coor_y[i - 1]) > eps))
		{
			if (point_belon_segm(coor_x[i - 1], coor_y[i - 1], coor_x[i], coor_y[i], x, y) == 1)
                        {
                                return -1;
                        }
			else if ((fabs(b0 * (coor_x[i] - x) - (a0 * (coor_y[i] - y))) < eps) && (a0 * (coor_x[i] - x) > 0))
			{
				count += 0;
			}
			else
			{
				count += intersec_ray_segm(x, y, a0, b0, coor_x[i - 1], coor_y[i - 1], coor_x[i] - coor_x[i - 1], coor_y[i] - coor_y[i - 1]);
			}
			printf("%d \n", count);
		}
	}
	if (point_belon_segm(coor_x[len -1], coor_y[len - 1], coor_x[0], coor_y[0], x, y) == 1)
        {
                return -1;
        }
	if ((fabs(b0 * (coor_x[0] - x) - (a0 * (coor_y[0] - y))) < eps) && (a0 * (coor_x[0] - x) > 0))
        {
        	count += 0;
        }
	else
	{
		count += intersec_ray_segm(x, y, a0, b0, coor_x[len - 1], coor_y[len - 1], coor_x[0] - coor_x[len - 1], coor_y[0] - coor_y[len - 1]);
        }
	printf("%d \n", count);
	return (count % 2);
}


int main(void)
{
	int i, len, result;
	FILE *input, *output;
	double *coor_x, *coor_y;
	double x, y;
	input = fopen("input.txt", "r");
	output = fopen("output.txt", "w");
	if ((input == NULL) || (output == NULL) || (feof(input) != 0))
	{
		printf("проблема с файлом");
		return -1;
	}
	if (fscanf(input, "%d", &len) != 1)
	{
		printf("проблема считывания из файла количества точек");
		return -1;
	}
	coor_x = (double *)malloc(len * sizeof(double));
	coor_y = (double *)malloc(len * sizeof(double));
	for (i = 0; i < len; i++)
	{
		if (fscanf(input, "%lf %lf", &coor_x[i], &coor_y[i]) != 2)
		{
			printf("проверьте, что в файле после длинны координаты записаны чкркз пробел");
			return -1;
		}
	}
	if (fscanf(input, "%lf %lf", &x, &y) != 2)
        {
                printf("проблема считывания из файла точки, у которой нужно определить положение относительно многоугольника");
                return -1;
        }
	if (len > 3)
	{
		result = determin_position_of_point(x, y, coor_x, coor_y, len);
	}
	else
	{
		result = -2;
	}
	if (result == 1)
	{
		fprintf(output, "точка находится внутри многоугольника");
	}
	else if (result == 0)
	{
		fprintf(output, "точка находится снаружи многоугольника");
	}
	else if (result == -1)
	{
		fprintf(output, "точка находится на границе многоугольника");
	}
	else
	{
		printf("это не многоугольник");
		return -1;
	}
	fclose(input);
	fclose(output);
	free(coor_x);
	free(coor_y);
	return 0;
}
