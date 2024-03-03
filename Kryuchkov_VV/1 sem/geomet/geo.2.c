#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int sgn_square (int x1, int y1,int x2, int y2, int x3, int y3); //Определяет знак ориентированной площади
int bulge (int *ver, int n); //Определяет выпуклость

int sgn_square (int x1, int y1, int x2, int y2, int x3, int y3)
{
    int ax, ay, bx, by;
    ax = x2 - x1;
    ay = y2 - y1;
    bx = x3 - x1;
    by = y3 - y1;

    if ((ax * by - ay * bx) > 0 )
    {
        return 1;
    }

    return -1;
}

int bulge (int *ver, int n)
{
    int count;
    count = 0;

    for (int i = 0; i < n; i++)
    {
        count = count + sgn_square (ver[i], ver[i + 1], ver[(i + 2) % n], ver[(i + 3) % n], ver[(i + 4) % n], ver[(i + 5) % n]);
    }

    if (count < 0)
    {
        count = - count;
    }

    if (count * 2 == n)
    {
        printf ("Выпуклый\n");
    }

    if (count * 2 != n)
    {
        printf ("Невыпуклый\n");
    }

    return 1;
}

int main (void)
{
    int n, check;
    int *ver;
    FILE *f_in;
    printf ("Введите координаты вершин в файл input.txt\n");
    printf ("Введите колчество вершин которые вы хотите задействовать \n");
    check = scanf ("%d", &n);

    if (check == 0)
    {
        printf ("Ошибка\n");
        return -1;
    }

    if (n < 3)
    {
        printf ("Требуется больше точек\n");
        return -1;
    }
    f_in = fopen ("input.txt", "r");
    if (f_in == NULL)
    {
        printf ("Вы не ввели координаты");
        return -1;
    }

    n = n * 2;

    ver = (int *)malloc(n*sizeof(int));

    for (int i = 0; i < n; i++)
    {
        check = fscanf (f_in, "%d", & ver[i]);
        if (check == 0)
        {
            printf ("Ошибка\n");
            free (ver);
            fclose (f_in);
            return -1;
        }

        bulge (ver, n);

        free (ver);
        fclose (f_in);

        return 0;
    }

}