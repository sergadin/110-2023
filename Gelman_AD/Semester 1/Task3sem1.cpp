#include<math.h>
#include<stdio.h>
#include<stdbool.h>

int incrsect(float a, FILE* inp);
int incrsect(float a, FILE* inp)
{
    int n = 0;
    float b;
    bool check = 1; //the sequence is increasing
    //check = 0 => the sequence is decreasing

    while (fscanf(inp, "%f", &b) > 0)
    {
        if (a > b)
        {
            if (check) //the sequence is increasing
            {
                n++;
                check = 0;
            }
        }
        else //(a < b)
        {
            check = 1;
        }
        a = b;
    }

    if (check == 1)
    {
        n++;
    }

    printf("Number of increasing sequence sections = %d\n", n);
    return 0;
}

int main() 
{
    float a;
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

    incrsect(a, inp);

    fclose(inp);
    return 0;
}