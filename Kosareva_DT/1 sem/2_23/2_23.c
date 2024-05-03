#include <stdio.h>
#include <stdlib.h>

int addition(int *a, int n);
int subtraction(int *a, int n);
int main(void);

int main(void) {
        int check, n, action, i;
        FILE *f;
        int *a = NULL;
	
        check = scanf("%d", &n);
        if (check == -1) {
                printf("Не указана длина массива\n");
                return -2;
        }
        if (check == 0) {
                printf("Ошибка данных\n");
                return -2;
        }

        f = fopen("a", "r");
        if (f == NULL) {
                printf("Не удалось открыть файл\n");
                return -1;
        }
        
        a = (int *)malloc((n+1)*sizeof(int));
        for (i=1; i<n+1; i++) {
                check = fscanf(f, "%1d", &a[i]);
                if (check != 1) {
                	free(a);
                        printf("Ошибка данных\n");
                        fclose(f);
                        return -2;
                }
        }
        
        fclose(f);
        
        check = scanf("%d", &action);
        if (check == -1) {
                printf("Не указано действие\n");
                free(a);
                return -2;
        }
        if (check == 0) {
                printf("Ошибка данных\n");
                free(a);
                return -2;
        }
        
        if (action == 1) {
            addition(a, n);
        }
        else if (action == -1) {
            subtraction(a, n);
        }
        else {
            printf("Ошибка данных\n");
                    return -2;
            }
        
        f = fopen("a", "w");
       	i = 0;
       	while (a[i] == 0) {
       		i++;
       	}
       	while (i<=n) {
       		fprintf(f, "%d ", a[i]);
       		i++;
       	}
       	free(a);
       	fclose(f);
       		
        return 0;
}

int addition(int *a, int n) {
	int i = n;
	a[0] = 0;
	
	while (i>=0) {
		if (a[i] < 9) {
			a[i]++;
			break;
		}
		else {
			a[i] = 0;
			i--;
		}
	}
	
	return 0;
}

int subtraction(int *a, int n) {
        int i = n;
      	a[0] = 1;
      	
      	while (i>0) {
            if (a[i] > 0) {
                a[i]--;
                i = 0;
            }
            else {
                a[i] = 9;
                i--;
            }
        }
        a[0] = 0;
        
        return 0;
}
