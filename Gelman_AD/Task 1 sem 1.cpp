#include <stdio.h>
#define E 0.1
int main(void)

{
    FILE* f;
    int current;
    int count = 3;
    f = fopen("input.txt", "r");
    float a = 10;
    float b = 100;
    float c = 1000;
    int d, e, g, h;

    if(f == NULL)
    {
        printf("���� �� ��������\�");
        return -1;
    }

    if(fscanf(f, "%f", &a) != 1) && (fscanf(f, "%f", &b) != 1)
    {
        printf("������ ������\n");
        return -1;
    }

    printf("������� ������������\n");
    scanf("%d", & d);
    scanf("%d", & e);
    scanf("%d", & g);
    scanf("%d", &h);


    while((fscanf(f, "%f", &c) == 1))
    {
        if ((d * a + e * b + g * c >= h*(E+1) ) && (*a + e * b + g * c <= h*(1-E) ))
        {
            printf("������������������ �� ������������� ��������� �� %s ������\n", count);
            return 0;
        }
        a = c;
        current = a;
        b = current;
        count++;
    }
    printf("������������������ ������������� ���������\n");
    return 0;
}