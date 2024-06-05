#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "find_difference.h"

typedef struct
{
    const char* fileA;
    const char* fileB;
    const char* fout;
} Test;


int main(void) {
    Test tests[] = {
        {"A1.txt", "B1.txt", "out1.txt"},
        {"A2.txt", "B2.txt", "out2.txt"},
        {"A3.txt", "B3.txt", "out3.txt"}
    };
    Error error;
    for (int i = 0; i < 3; i ++) {
        find_difference(tests[i].fileA, tests[i].fileB, tests[i].fout, &error);
        if (error == INP) {
            printf("Неверные входные данные\n");
            return -1;
        } else if (error == OUTP) {
            printf("Ошибка открытия файла для записи результата\n");
            return -1;
        }
    }

    return 0;

}