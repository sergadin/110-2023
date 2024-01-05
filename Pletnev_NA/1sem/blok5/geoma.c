#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define YES 222
#define NO -222
#define eps 1e-10

int CheckPolyline(double *arrX, double *arrY, int n);
void ArrP(double *arrX, double *arrY, double *arrA, double *arrB, double *arrC, int n);
int LenSet(double *arrX, double *arrY, int len);
double Max(double h1, double h2);
double Min(double h1, double h2);
int CheckLines(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4,
               double A1, double B1, double C1, double A2, double B2, double C2);

double Max(double h1, double h2)
{
    if (h1 > h2)
    {
        return h1;
    }

    return h2;
}

double Min(double h1, double h2)
{
    if (h1 > h2)
    {
        return h2;
    }

    return h1;
}

int CheckLines(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4,
               double A1, double B1, double C1, double A2, double B2, double C2)
{
    double y;
    double x;

    if (((x2 - x3) <= eps) && ((y2 - y3) <= eps))
    {
        if ((fabs(A1 * B2 - A2 * B1) <= eps) && (fabs(A1 * C2 - A2 * C1) <= eps) && (fabs(B1 * C2 - B2 * C1) <= eps))
        {

            if (fabs(A1) <= eps)
            {
                if (B2 / B1 < 0)
                {
                    if (((Min(x3, x4) < x2) && (x2 < Max(x3, x4))) || (((Min(x1, x2) < x4) && (x4 < Max(x1, x2)))))
                    {
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
            }

            if (fabs(B1) < eps)
            {

                if (A2 / A1 < 0)
                {
                    if (((Min(y3, y4) < y2) && (y2 < Max(y3, y4))) || ((Min(y1, y2) < y4) && (y4 < Max(y1, y2))))
                    {
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
            }

            if (A2 / A1 < 0)
            {
                if (((Min(x3, x4) <= x2) && (x2 <= Max(x3, x4))) || (((Min(x1, x2) <= x4) && (x4 <= Max(x1, x2)))))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }

            return 0;
        }

        return 0;
    }

    if ((fabs(A1 * B2 - A2 * B1) <= eps) && (fabs(A1 * C2 - A2 * C1) <= eps) && (fabs(B1 * C2 - B2 * C1) <= eps))
    {

        if (fabs(A1) <= eps)
        {
            if (B2 / B1 < 0)
            {
                if (((Min(x3, x4) <= x2) && (x2 <= Max(x3, x4))) || (((Min(x1, x2) <= x4) && (x4 <= Max(x1, x2)))))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
        }

        if (fabs(B1) < eps)
        {

            if (A2 / A1 < 0)
            {
                if (((Min(y3, y4) <= y2) && (y2 <= Max(y3, y4))) || ((Min(y1, y2) <= y4) && (y4 <= Max(y1, y2))))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
        }

        if (A2 / A1 < 0)
        {
            if (((Min(x3, x4) <= x2) && (x2 <= Max(x3, x4))) || (((Min(x1, x2) <= x4) && (x4 <= Max(x1, x2)))))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }

        return 0;
    }

    if ((fabs(A1 * B2 - A2 * B1) <= eps) && (fabs(A1 * C2 - A2 * C1) > eps))
    {
        return 0;
    }

    if ((fabs(A1 * B2 - A2 * B1) <= eps) && (fabs(B1 * C2 - B2 * C1) > eps))
    {
        return 0;
    }

    if ((fabs(x1 - x4) <= eps) && (fabs(y1 - y4)) <= eps)
    {
        return 0;
    }

    if (fabs(A1) <= eps)
    {
        y = -C1 / B1;

        if (!((Min(y1, y2) <= y) && (y <= Max(y1, y2)) && (Min(y3, y4) <= y) && (y <= Max(y3, y4))))
        {
            return 0;
        }

        x = (-C2 - B2 * y) / A2;

        if (!((Min(x1, x2) <= x) && (x <= Max(x1, x2)) && (Min(x3, x4) <= x) && (x <= Max(x3, x4))))
        {
            return 0;
        }

        return 1;
    }

    if (fabs(B1) <= eps)
    {

        x = -C1 / A1;

        if (!((Min(x1, x2) <= x) && (x <= Max(x1, x2)) && (Min(x3, x4) <= x) && (x <= Max(x3, x4))))
        {
            return 0;
        }

        y = (-C2 - A2 * x) / B2;

        if (!((Min(y1, y2) <= y) && (y <= Max(y1, y2)) && (Min(y3, y4) <= y) && (y <= Max(y3, y4))))
        {
            return 0;
        }

        return 1;
    }

    y = (C1 * A2 - C2 * A1) / (A1 * B2 - A2 * B1);

    if (!((Min(y1, y2) <= y) && (y <= Max(y1, y2)) && (Min(y3, y4) <= y) && (y <= Max(y3, y4))))
    {
        return 0;
    }

    x = (B1 * y + C1) / (-A1);

    if (!((Min(x1, x2) <= x) && (x <= Max(x1, x2)) && (Min(x3, x4) <= x) && (x <= Max(x3, x4))))
    {
        return 0;
    }

    return 1;
}

int LenSet(double *arrX, double *arrY, int len)
{

    int i = 1;

    for (int j = 1; j < len; j++)
    {
        if ((fabs(arrX[j] - arrX[i - 1]) > eps) || (fabs(arrY[j] - arrY[i - 1]) > eps))
        {
            arrX[i] = arrX[j];
            arrY[i] = arrY[j];
            i++;
        }
    }

    return i;
}

void ArrP(double *arrX, double *arrY, double *arrA, double *arrB, double *arrC, int n)
{
    double A;
    double B;
    double C;
    double x1, y1;
    double x2, y2;

    for (int i = 0; i < n - 1; i++)
    {
        x1 = arrX[i];
        y1 = arrY[i];

        x2 = arrX[i + 1];
        y2 = arrY[i + 1];

        A = y2 - y1;
        B = -(x2 - x1);
        C = -B * y1 - A * x1;

        arrA[i] = A;
        arrB[i] = B;
        arrC[i] = C;
    }
}

int CheckPolyline(double *arrX, double *arrY, int n)
{
    double *arrA;
    double *arrB;
    double *arrC;

    double x1, y1;
    double x2, y2;
    double x3, y3;
    double x4, y4;

    double A1, B1, C1;
    double A2, B2, C2;

    int i;
    int j;

    arrA = (double *)malloc((n - 1) * sizeof(double));
    arrB = (double *)malloc((n - 1) * sizeof(double));
    arrC = (double *)malloc((n - 1) * sizeof(double));

    ArrP(arrX, arrY, arrA, arrB, arrC, n);

    // for (int i = 0; i < n - 1; i++)
    // {
    //     printf("(%lf) * x + (%lf) * y + (%lf) = 0\n", arrA[i], arrB[i], arrC[i]);
    // }

    // return NO;

    if (n == 3)
    {
        i = 0;
        j = 1;

        x1 = arrX[i];
        y1 = arrY[i];

        x2 = arrX[i + 1];
        y2 = arrY[i + 1];

        x3 = arrX[j];
        y3 = arrY[j];

        x4 = arrX[j + 1];
        y4 = arrY[j + 1];

        A1 = arrA[i];
        B1 = arrB[i];
        C1 = arrC[i];

        A2 = arrA[j];
        B2 = arrB[j];
        C2 = arrC[j];

        if (CheckLines(x1, y1, x2, y2, x3, y3, x4, y4, A1, B1, C1, A2, B2, C2))
        {
            free(arrA);
            free(arrB);
            free(arrC);
            return NO;
        }
    }

    for (int i = 0; i < n - 2; i++)
    {
        for (int j = i + 1; i < n - 1; i++)
        {
            x1 = arrX[i];
            y1 = arrY[i];

            x2 = arrX[i + 1];
            y2 = arrY[i + 1];

            x3 = arrX[j];
            y3 = arrY[j];

            x4 = arrX[j + 1];
            y4 = arrY[j + 1];

            A1 = arrA[i];
            B1 = arrB[i];
            C1 = arrC[i];

            A2 = arrA[j];
            B2 = arrB[j];
            C2 = arrC[j];

            if (CheckLines(x1, y1, x2, y2, x3, y3, x4, y4, A1, B1, C1, A2, B2, C2))
            {
                free(arrA);
                free(arrB);
                free(arrC);
                return NO;
            }
        }
    }

    free(arrA);
    free(arrB);
    free(arrC);
    return YES;
}

int main(void)
{
    int n;

    double x;
    double y;

    double *arrX;
    double *arrY;

    int res;

    printf("Enter number of points that define the polyline:\n");
    scanf("%d", &n);

    if (n < 0)
    {
        printf("Error: incorrect data entry");
        goto end0;
    }

    arrX = (double *)malloc(n * sizeof(double));
    arrY = (double *)malloc(n * sizeof(double));

    for (int j = 0; j < n; j++)
    {
        printf("Enter the coordinates of point № %d\n", j + 1);
        scanf("%lf", &x);
        scanf("%lf", &y);

        arrX[j] = x;
        arrY[j] = y;
    }

    n = LenSet(arrX, arrY, n);

    res = CheckPolyline(arrX, arrY, n);

    if (res == NO)
    {
        printf("The polyline intersects itself");
        goto end;
    }

    printf("The polyline does not intersect itself");

end:

    free(arrX);
    free(arrY);

end0:

    return YES;
}