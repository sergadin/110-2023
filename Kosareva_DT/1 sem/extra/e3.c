 #include <stdio.h>
#include <stdlib.h>

int count(FILE *f);
int func(int *a, int n, FILE *f);
int main(void);

int count(FILE *f) {
    int check, n, x;
    n = 0;
    check=fscanf(f, "%d", &x);
    while(check == 1) {
        n++;
        check=fscanf(f, "%d", &x);
    }
    if (check == 0) {
        return -1;
    }
    return n;
}

int func(int *a, int n, FILE *f) {
    int i, full;
    
    full = 1;
    for (i=0; i<n; i++) {
        full = full * a[i];
    }
    
    
    for (i=0; i<n; i++) {
        fprintf(f, "%d ", full/a[i]);
    }
    
    return 0;
}

int main(void) {
    int *a = NULL;
    FILE *f;
    int n, i;
    
    f = fopen("in.txt", "r");
    if (f == NULL) {
        return -1;
    }
    
    n = count(f);
    fclose(f);
    if (n < 1) {
        return -1;
    }
    
    f = fopen("in.txt", "r");
    if (f == NULL) {
        return -1;
    }
    
    a = (int *)malloc(n*sizeof(int));
    if (a == NULL) {
        fclose(f);
        return -1;
    }
    for (i=0; i<n; i++) {
        fscanf(f, "%d", &a[i]);
    }
    fclose(f);
    
    f = fopen("out.txt", "w");
    if (f == NULL) {
        free(a);
        return -1;
    }
    
    func(a, n, f);
    
    fclose(f);
    free(a);
    return 0;
}
