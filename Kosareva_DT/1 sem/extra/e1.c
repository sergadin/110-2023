#include <stdio.h>
#include <stdlib.h>

int count(FILE *f);
int h(int *a, int n, int l, int r);
int main(void);

int count(FILE *f) {
    int check, n, x;
    n = 0;
    check=fscanf(f, "%d", &x);
    while(check == 1) {
        if (x < 0) {
            return -1;
        }
        n++;
        check=fscanf(f, "%d", &x);
    }
    if (check == 0) {
        return -1;
    }
    return n;
}

int h(int *a, int n, int l, int r) {
    int i, mid, count;
    count = 0;
    
    if (l == r) {
        return l;
    }
    
    mid = (l + r + 1)/2;
    for (i=0; i<n; i++) {
        if (a[i] >= mid) {
            count++;
        }
    }
    if (count < mid) {
        return h(a, n, l, mid-1);
    }
    else {
        return h(a, n, mid, r);
    }
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
    
    printf("%d\n", h(a, n, 0, n));
    
    free(a);
    return 0;
}  
