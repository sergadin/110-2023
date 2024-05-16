#include <stdio.h>
#include <stdlib.h>
#include <math.h>﻿
#include "interpolation.h"

// Функция для вычисления значения функции на заданной точке
double interpolate(double x[], double y[], int n, double x1) 
{
    double result = 0;

    for (int i = 0; i < n - 1; i++) 
    {
        if (x1 >= x[i] && x1 <= x[i + 1]) 
        {
            result = y[i] + (y[i + 1] - y[i]) / (x[i + 1] - x[i]) * (x1 - x[i]);
            break;
        }
    }
    return result;
}

void interpolate(point* p, size_t n, point* i_p, size_t m, double* interp_y, error* err)
{
    // int n = 5; // количество точек
    *err = OK;
    double x[] = { 0, 1, 2, 3, 4 }; // заданные точки x
    double y[] = { 0, 1, 4, 9, 16 }; // значения функции y на заданных точках x

    int n1 = 100; // количество точек на сетке для интерполяции
    double x1[n1]; // точки на сетке для интерполяции
    double y1[n1]; // значения функции на точках сетки для интерполяции

    // Заполнение точек на сетке для интерполяции
    for (int i = 0; i < n1; i++) 
    {
        x1[i] = i * (double)(n - 1) / (n1 - 1); // интервал [0, 4] равномерно разбиваем на n1 точек
        y1[i] = interpolate(x, y, n, x1[i]); // используем кусочно-линейную интерполяцию
    }

    // Сравнение с точными значениями функции
    printf("Точки на сетке для интерполяции и их приближенные значения:\n");
    for (int i = 0; i < n1; i++) 
    {
        printf("x1[%d] = %.2f, y1[%d] = %.2f, y_exact = %.2f\n", i, x1[i], i, y1[i], x1[i] * x1[i]);
    }

    // Запись данных в файл для построения графика в Gnuplot
    FILE* f = fopen("data.txt", "w");
    for (int i = 0; i < n1; i++) 
    {
        fprintf(f, "%f %f\n", x1[i], y1[i]);
    }
    fclose(f);

    return 0;
}

/*
void interpolate(point* p, size_t n, point* i_p, size_t m, double* interp_y, error* err) 
{
    *err = OK;
    for (int j = 0; j < m; j++) 
    {
        double x2, y2;

        int i;                    // Поиск отрезка, в который попадает x
        for (i = 1; i < n; ++i) 
        {
            if (p[i].x >= i_p[j].x)
                break;
        }

        double x0 = p[i - 1].x, x1 = p[i].x,
               y0 = p[i - 1].y, y1 = p[i].y,
               x = i_p[j].x;

        if (i < n - 1) 
        {          // Вычисление значения на отрезке с помощью кусочно-квадратичной интерполяции
            x2 = p[i + 1].x;
            y2 = p[i + 1].y;
        }
        else 
        {                    // Если последняя точка, то выбираем предпоследнюю
            x2 = p[i - 1].x;
            y2 = p[i - 1].y;
        }

        double L0 = ((x - x1) * (x - x2)) / ((x0 - x1) * (x0 - x2));     // Весовые коэффиценты
        double L1 = ((x - x0) * (x - x2)) / ((x1 - x0) * (x1 - x2));
        double L2 = ((x - x0) * (x - x1)) / ((x2 - x0) * (x2 - x1));

        double result = y0 * L0 + y1 * L1 + y2 * L2;

        interp_y[j] = result;
    }
}
*/