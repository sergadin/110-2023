#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define LIMIT 100000

typedef enum
{
  OK,
  ERROR_Divide_by_zero,
  ERROR_LIMIT,
} ERROR;

void speedy_descent (int N, double *matr, double *vector_b, double *vector_x, double epsilon, ERROR * error);
static void product_Ax (int N, double *matr, double *vector_x, double *vector_result);
static void product_Atx (int N, double *matr, double *vector_x, double *vector_result);
static double scalar_product (int n, double *vector_a, double *vector_b);
