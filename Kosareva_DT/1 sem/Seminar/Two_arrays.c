 #include <stdio.h>
#include <stdlib.h>

int main(void);
int min(int a, int b);
int good(double *a, double *b, int n, int m);

int min(int a, int b) {
    if (a>b) {
        return b;
    }
    return a;
}

int good(double *a, double *b, int n, int m) {
    int i, new;
    for (i=1; i<min(m, n); i++) {
        b[i]+=b[i-1];
    }
    new = 1;
    
    for (i=1; i<n; i++) {
        if (a[i] > b[min(m-1, i-1)]) {
            a[new] = a[i];
            new++;
        }
    }
    
    return new;
}

int main(void) {
    FILE *f;
    double *a = NULL;
    double *b = NULL;
    int i, n, m, check;
    
    f = fopen("input.txt", "r");
    if (f == NULL) {
        return -1;
    }
    
    check = fscanf(f, "%d", &n);
    if (check != 1) {
        return -1;
    }
    check = fscanf(f, "%d", &m);
    if (check != 1) {
        return -1;
    }
    
    a = (double *)malloc(n*sizeof(double));
    b = (double *)malloc(m*sizeof(double));
    
    for (i=0; i<n; i++) {
        check = fscanf(f, "%lf", &a[i]);
        if (check != 1) {
            free(a);
            free(b);
            return -1;
        }
    }
    for (i=0; i<m; i++) {
        check = fscanf(f, "%lf", &b[i]);
        if (check != 1) {
            free(a);
            free(b);
            return -1;
        }
    }
        
    fclose(f);
    
    f = fopen("output.txt", "w");
    if (f == NULL) {
        free(a);
        free(b);
        return -1;
    }
    
    n = good(a, b, n, m);
    for (i=0; i<n; i++) {
        fprintf(f, "%lf ", a[i]);
    }
    
    fclose(f);
    free(a);
    free(b);
    
    return 0;
}
