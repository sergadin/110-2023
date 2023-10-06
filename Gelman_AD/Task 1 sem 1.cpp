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
        printf("File did not open\n");
        return -1;
    }

    if((fscanf(f, "%f", &a) != 1) && (fscanf(f, "%f", &b) != 1))
    {
        printf("Reading error\n");
        return -1;
    }

    printf("Enter multipliers\n");
    scanf("%d", & d);
    scanf("%d", & e);
    scanf("%d", & g);
    scanf("%d", &h);


    while((fscanf(f, "%f", &c) == 1))
    {
        if ((d * a + e * b + g * c >= h*(E+1) ) && (d*a + e * b + g * c <= h*(1-E) ))
        {
            printf("The sequence does not satisfy the expression at number  %d \n", count);
            return 0;
        }
        a = c;
        current = a;
        b = current;
        count++;
    }
    printf("The sequence satisfies the expression\n");
    return 0;
}