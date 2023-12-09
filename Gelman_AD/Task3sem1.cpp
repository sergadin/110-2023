#include<math.h>
#include<stdio.h>
#include<stdbool.h>

int incrsect(FILE* inp);
int incrsect(FILE* inp)
{
    int n = 0;
    float a;
    float b;
    bool nonincr = 1; //the sequence is increasing
    //check = 0 => the sequence is decreasing

    if (fscanf(inp, "%f", &a) != 1)
    {
        printf("Unable to read the first element\n");
        return 0;
    }

    while (fscanf(inp, "%f", &b) > 0)
    {
        if (a > b)
        {
            if (nonincr) //the sequence is increasing
            {
                n++;
                nonincr = 0;
            }
        }
        else //(a <= b)
        {
            nonincr = 1;
        }
        a = b;
    }

    if (nonincr == 1)
    {
        n++;
    }

    printf("Number of increasing sequence sections = %d\n", n);
    return 0;
}

int main() 
{
    FILE* inp;

    inp = fopen("input.txt", "r");
    
    if (inp == NULL) 
    {
        printf("Unable to open file\n");
        return 0;
    }

    incrsect(inp);

    fclose(inp);
    return 0;
}