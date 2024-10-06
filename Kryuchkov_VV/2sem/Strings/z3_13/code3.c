#include <stdio.h>
#include <math.h>

void main()
{
    #ifdef Abla 
    printf("In cycle\n");
    #else
    printf("Wrong\n");
    #endif
    printf("Cycle end\n");
}