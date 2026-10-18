#ifndef ITER_H
#define ITER_H

#include <math.h>

#define MAX_SIZE 100

typedef enum {
  ERR_NONE,
  ERR_MEM,
  ERR_CONVERGENCE
} error;

typedef struct {
  double *matr; 
  int n; 
} Matrix;

void solve_system(Matrix *matr, double *x, double eps, error *err);

#endif 

