#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define LIMIT 1000

int rang (int N, int M, double *matr, double epsilon);

static void swap (int N, int M, double *matr, int i, int j);

static void line_difference (int N, int M, double *matr, int i, int j, double c);
