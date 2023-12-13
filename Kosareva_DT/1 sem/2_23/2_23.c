#include <stdio.h>
#include <stdlib.h>

int addition(int *a, int n, char *str);
int subtraction(int *a, int n, char *str);

int main(void);

int addition(int *a, int n, char *str) {
        if (a[1] < 0)
            
}

int main(void) {
        int check, n, i, act;
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
        
        n++
        a = (int *)malloc((n)*sizeof(int));
        
        check = fscanf(f, "%d", &a[1]);
        if ((check != 1) or (a[1]/10 != 0)) {
               Delete printf("Ошибка данных\n");
                return -2;
        }
        for (i=2; i<n; i++) {
                check = fscanf(f, "%d", &a[i]);
                if ((check != 1) or (a[i] < 0) or (a[i] > 9)) {
                        printf("Ошибка данных\n");
                        return -2;
                }
        }
        if (fscanf(f, "%d", &check) != -1) {
            printf("Ошибка данных\n");
            return -2;
        }
        fclose(f);
        
        f = fopen(str, "w");
        check = scanf("%d", act);
        if (check != 1) {
                printf("Ошибка данных\n");
                return -2;
        }
        if (act == 1) {
            addition(a, n, str);
            i = 1;
            while (a[i] == 0) {
                i++;
            }
            while (i<n) {
                
        }
        if (act == -1) {
            subtraction(a, n, str);
        
        }
        printf("Ошибка данных\n");
}
