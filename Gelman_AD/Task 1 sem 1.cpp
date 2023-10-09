#include <stdio.h>
#include <math.h>
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
    double E = 0.1;

    if(f == NULL)
    {
        printf("File did not open\n");
        return -1;
    }

    if((fscanf(f, "%f", &a) != 1)
    {
        printf("Reading error\n");
        return -1;
    }
    else
    {
        if (fscanf(f, "%f", &b) != 1)
        {
            printf("Reading error\n");
            return -1;
        }
    }

    printf("Enter multipliers\n");
    scanf("%d", & d);
    scanf("%d", & e);
    scanf("%d", & g);
    scanf("%d", &h);


    while((fscanf(f, "%f", &c) == 1))
    {
        if (((d * a + e * b + g * c) - h) >= E)
        {
            printf("The sequence does not satisfy the expression at number  %d \n", count);
            fclose(f);
            return 0;
        }
        current = a;
        a = b;
        b = current;
        count++;
    }
    printf("The sequence satisfies the expression\n");
    fclose(f);
    return 0;
}