#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    OK,              // Все хорошо
    NO_SOLUTION,     // Система не определена
    NOT_DET
}error;

void writeMatrix(double* matrix, size_t m, size_t n);

double* solution(double* matrix, size_t m, size_t n, error* err);