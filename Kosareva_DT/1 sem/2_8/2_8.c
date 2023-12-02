#include <stdio.h>

int Delete(FILE *f, int n, char *str);
int main(void);

int Delete(FILE *f, int n, char *str) {
	int a[n], i, j, check;

	for (i=0; i<n; i++) {
		check = fscanf(f, "%d", &a[i]);
		if (check != 1) {
			printf("Ошибка данных3\n");
			return -2;
		}
	}
	fclose(f);

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
        i++;
    }
    
	f = fopen(str, "w");
	fprintf(f, "%d ", n);
	for (i=0; i<n; i++) {
		fprintf(f, "%d ", a[i]);
	}
	return 0;
}
int main(void) {
	int check, n;
	FILE *f;
	char str[60];

	check = scanf("%s", str);
	if (check == 0) {
		printf("Не указано имя массива\n");
		return -2;
	}
	if (check == -1) {
		printf("Ошибка данных1\n");
		return -2;
	}
	
	f = fopen(str, "r");
	if (f == NULL) {
		printf("Не удалось открыть файл\n");
		return -1;
	}

	check = fscanf(f, "%d", &n);
	if (check == -1) {
		printf("Не указана длинна массива\n");
		return -2;
	}
	if (check == 0) {
		printf("Ошибка данных2\n");
		return -2;
	}
	Delete(f, n, str);
	fclose(f);
}
