#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formate.h"

typedef struct
{
    const char* fileA;
    const char* fout;
    int width;
} Test;


int main(void) {
    Error error;
    Test tests[] = {
        {"A1.txt", "B1.txt", 60},
        {"A2.txt", "B2.txt", 70},
        {"A3.txt", "B2.txt", 4},
    };
    for (int i = 0; i < 3; i ++) {
        formate(tests[i].fileA, tests[i].fout, tests[i].width, &error);
        if (error == INP) {
            printf("Не удалось открыть файл с входными данными\n");
        } else if (error == OUTP) {
            printf("Не удалось открыть файл для выходных данных");
        }
    }

    return 0;

}