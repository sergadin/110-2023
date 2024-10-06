#ifndef ITER_H
#define ITER_H

#define MAX_SIZE 100

typedef enum {
	ERR_NONE,
	ERR_MEM,
	ERR_CONVERGENCE
} error;

typedef struct {
	int n;
	double *matr;
	double *b; 
} Matrix;

Matrix* create_matrix(int n);
void free_matrix(Matrix *matr);
void solve_system(Matrix *matr, double *x, double eps, error *err);

#endif
