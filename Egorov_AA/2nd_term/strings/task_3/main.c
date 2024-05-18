#include <stdio.h>
#include <stdlib.h>
#include "strings.c"


int main(void) {
    const char* input = "input.txt";
    const char* output= "output.txt";

    copyWords(input, output);

    //потом тест сделаю?

    return 0;
}
