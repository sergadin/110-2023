#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "det.h"

void create_minor(double * matr, double *minor, int n, int m);

void create_minor(double * matr, double *minor, int n, int m)
{
    int j = 0;
    for(int i = n; i < n * n; i++)
    {
        if(i % n != m){
            minor[j] = matr[i];
            j++;
        }
    }
}

double determinate(double *matr, int n, Error *err)
{
    double det = 0;
    double* minor = 0;
    int sgn = 1;
    *err = OK;
    if(n == 0)
    {
        *err = ZER_MAT;
        return -1;
    }
    if(n == 1)
    {
        return matr[0];
    }
    if(n == 2){
        return((matr[0] * matr[3]) - matr[1] * matr[2]);
    }
    minor = (double *)malloc(((n - 1) * (n - 1)) * sizeof(double));
    for (int i = 0; i < n; i++)
    {
        if (minor == NULL)
        {
		    printf("Оперативная память не выделена\n");
		    *err = MEM_ER;
		    return -1;
	    }

    	create_minor(matr, minor, n, i);
        det  += sgn * matr[i] * determinate(minor, n-1,err);
        sgn *= -1;
        
    }
    free(minor);
    return det;
}
