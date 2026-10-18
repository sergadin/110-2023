#include <stdio.h>
#define Macr(a, b) (a)*(a+b)

#define New_invisible 56

void main(){
    int a = 0;
    #ifdef Mar
    printf("Hello, world\n");
    #endif
    #ifdef New_invisible
    a+=7;
    #else
    a-=10;
    #endif
    printf("Save our souls!\n");
}