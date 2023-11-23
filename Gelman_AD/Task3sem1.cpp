#include<math.h>
#include<stdio.h>
#include<stdbool.h>

int incrsect(bool check, float a, float b, FILE* inp);
int incrsect(bool check, float a, float b, FILE* inp)
{
    int n = 0;
    bool check = 1;

    while (fscanf(inp, "%f", &b) > 0)
    {
        if (a > b)
        {
            if (check)
            {
                n++;
                check = 0;
            }
        }
        else
        {
            check = 1;
        }
        a = b;
    }

    printf("Number of increasing sequence sections = %d\n", n);
    return 0;
}

int main() 
{
    int n = 0;
    bool check = 1;
    float a, b;
    FILE* inp;

    inp = fopen("input.txt", "r");
    
    if (inp == NULL) 
    {
        printf("Unable to open file\n");
        return 0;
    }
    
    if (fscanf(inp, "%f", &a) != 1) 
    {
        printf("Unable to read the first element\n");
        return 0;
    }

    incrsect(check, a, b, inp);

    fclose(inp);
    return 0;
}