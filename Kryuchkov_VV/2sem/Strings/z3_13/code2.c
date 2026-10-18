#include <stdio.h>
#include <math.h>
#define CONST

void main()
{
    for (int i = 0; i< 100; i++){
        #ifdef CONST 
        printf("In cycle\n");
        #else
        break;
        #endif
    }
    printf("Cycle end\n");
}