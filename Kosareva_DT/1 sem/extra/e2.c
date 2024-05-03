#include <stdio.h>
#include <stdlib.h>

int count(FILE *f);
int sort(int *X, int n);
int P(int *x, int n, FILE *f);
int main(void);

int count(FILE *f) {
    int check, n, l, r;
    n = 0;
    check=fscanf(f, "%d", &l);
    while(check == 1) {
        if (fscanf(f, "%d", &r) != 1) {
            return -1;
        }
        if (r < l) {
            return -1;
        }
        
        n++;
        check=fscanf(f, "%d", &l);
    }
    if (check == 0) {
        return -1;
    }
    return n;
}

int sort(int *X, int n) {
    int i, j, k;
    for (i=2*n-2; i>0; i-=2) {
        for (j=0; j<i; j+=2) {
            if (X[j] > X[j+2]) {
                k = X[j];
                X[j] = X[j+2];
                X[j+2] = k;
                k = X[j+1];
                X[j+1] = X[j+3];
                X[j+3] = k;
            }
        }
    }
    return 0;
}

int P(int *X, int n, FILE *f) {
    int i;
    for (i=0; i<2*n-2; i+=2) {
        if (X[i+2] <= X[i+1]) {
            if (X[i+1] < X[i+3]) {
                X[i+3] = X[i+1];
            }
        }
        else {
            fprintf(f, "%d ", X[i+1]);
        }
    }
    fprintf(f, "%d ", X[2*n-1]);
    
    return 0;
}

int main(void) {
    int *X = NULL;
    FILE *f;
    int n, i;
    
    f = fopen("in.txt", "r");
    if (f == NULL) {
        return -1;
    }
    
    n = count(f);
    fclose(f);
    if (n == -1) {
        return -1;
    }
    
    f = fopen("in.txt", "r");
    if (f == NULL) {
        return -1;
    }
    
    X = (int *)malloc(2*n*sizeof(int));
    if (X == NULL) {
        fclose(f);
        return -1;
    }
    for (i=0; i<2*n; i++) {
        fscanf(f, "%d", &X[i]);
    }
    fclose(f);
    
    sort(X, n);
    
    f = fopen("out.txt", "w");
    if (f == NULL) {
        free(X);
        return -1;
    }
    
    P(X, n, f);
    
    fclose(f);
    free(X);
    return 0;
}
