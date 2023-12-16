#include <stdio.h>
#include <stdlib.h>

int Delete(int *a, int n, char *str);
int main(void);

int Delete(int *a, int n, char *str) {
        int i, j;
        FILE *f;

        i = 0;
        while (i < n) {
            j = 0;
            while(a[j] != a[i]) {
                ++j;
            }
            if (j != i) {
                n--;
                for (j=i; j<n; j++) {
                    a[j] = a[j+1];
                }
            }
            else {
                i++;
            }
        }
        
        f = fopen(str, "w");
        for (i=0; i<n; i++) {
            fprintf(f, "%d ", a[i]);
        }
        fclose(f);
        return 0;
}
int main(void) {
        int check, n, i;
        int *a = NULL;
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
        
        a = (int *)malloc(n*sizeof(int));
        for (i=0; i<n; i++) {
                check = fscanf(f, "%d", &a[i]);
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
        
        Delete(a, n, str);
}
