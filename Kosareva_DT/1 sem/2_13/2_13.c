#include <stdio.h>
#include <stdlib.h>

int change (FILE *f, double *a, int n, char *str);
int main(void) {
        int check, n, i;
        double *a = NULL;
        FILE *f;
        char str[60];


        check = scanf("%s", str);
        if (check == -1) {
                printf("Не указано имя массива\n");
                return -2;
        }
        if (check == 0) {
                printf("Ошибка данных\n");
                return -2;
        }

        f = fopen(str, "r");
        if (f == NULL) {
            printf("Не удалось окрыть файл\n");
            return -1;
        }

        check = scanf("%d", &n);
        if (check == -1) {
                printf("Не указана длина массива\n");
                return -2;
        }
        if (check == 0) {
                printf("Ошибка данных\n");
                return -2;
        }
        
        a = (double *)malloc(n*sizeof(double));
        for (i=0; i<n; i++) {
                check = fscanf(f, "%lf", &a[i]);
                if (check != 1) {
                        printf("Ошибка данных\n");
                        return -2;
                }
        }
        if (fscanf(f, "%d", &check) != -1) {
            printf("Ошибка данных\n");
            return -2;
        }
        fclose(f);
        
        return change(f, a, n, str);
}

int change(FILE *f, double *a, int n, char *str) {
	
        double last, new;
        int i;

        if (n > 0) {
                last = a[0]/2;
            }
        for (i=1; i<n-1; i++) {
            new = a[i]/2;
            a[i] = last + a[i+1]/2;
            last = new;
        }
        
        f = fopen(str, "w");
        for (i=0; i<n; i++) {
            fprintf(f, "%f ", a[i]);
        }
        fclose(f);
        return 0;
}
