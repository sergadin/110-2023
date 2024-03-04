#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#define SIZE (sizeof(unsigned int) * 8)

int Mirror (unsigned int x);// Отражает биты
int Len (unsigned y); //Колтчество битов
void Print (unsigned int x, int len); //Записывает ответ

int Mirror (unsigned int x)
{
    int len;
    bool e1;
    bool e2;
    len = Len(x);
    for (int i = len - 1; i >= len / 2; i--)
    {
        e1 = ((1 << i) & x);
        e2 = ((1 << (len - 1 - i)) & x);

        x = (e2 << i) | ((~(1 << i)) & x);
        x = (e1 << (len - 1 - i)) | ((~(1 << (len - 1 - i))) & x);
    } 
    return x;
}

int Len (unsigned y)
{
    for (int i = SIZE - 1; i >= 0; i--)
    {
        if  (((1 << i) & y) != 0)
        {
            return i + 1;
        }
    }
    return 0;
}

void Print (unsigned int x, int len)
{
    for (int i = len - 1; i >= 0; i--)
    {
        if ((i % 8) == 0)
        {
            printf ("_");
        }
        if ((1 << i) & x)
        {
            printf ("%d", 1);
        }
        else
        {
            printf ("%d", 0);
        }
    }
    printf ("\n");
}

int main (void)
{
    unsigned int x;
    int len;

    printf( "Введите число:\n");
    scanf("%d", &x);
    len = Len(x);

	printf("Изначальная запись (%d):\n", x);
	Print(x, len);

    printf ("Зеркальная запись (%d):\n", x);
    Print (Mirror(x), len);
    return 0;
}
