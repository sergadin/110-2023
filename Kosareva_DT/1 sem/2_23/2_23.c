#include <stdio.h>

int addition(FILE *f, int n, char *str);
int subtraction(FILE *f, int n, char *str);
int main(void);

int addition(FILE *f, int n, char *str) {
	int check, a[n], i, one;

	a[0] = 0;
	for (i=1; i<n; i++) {
		check = fscanf(f, "%d", &a[i]);
		if (check != 1) {
			printf("Ошибка данных\n");
			return -2;
		}
		if (a[i] > 9) {
			printf("Ошибка данных\n");
                        return -2;
		}
	}
	fclose(f);
	
	one = 1;
	for (i=n-1; i>=0; i--) {
		a[i] += one;
		one = a[i]/10;
		a[i] = a[i]%10;
	}

	f = fopen(str, "w");
	one = 0;
	for (i=0; i<n; i++) {
		if (a[i] > 0) {
			one = 1;
		}
		if (one == 1) {
			fprintf(f, "%d ", a[i]);
		}
	}
	return 0;
}

int subtraction(FILE *f, int n, char *str) {
        int check, a[n], i, one;

        a[0] = 1;
        for (i=1; i<n; i++) {
                check = fscanf(f, "%d", &a[i]);
                if (check != 1) {
                        printf("Ошибка данных\n");
                        return -2;
                }
                if (a[i] > 9) {
                        printf("Ошибка данных\n");
                        return -2;
                }
        }
        fclose(f);

        one = 1;
        for (i=n-1; i>=0; i--) {
                a[i] += 10-one;
                one = 1 - a[i]/10;
                a[i] = a[i]%10;
        }

        f = fopen(str, "w");
        one = 0;
        for (i=1; i<n; i++) {
                if (a[i] > 0) {
                        one = 1;
                }
                if (one == 1) {
                        fprintf(f, "%d ", a[i]);
                }
        }
        return 0;
}

int main(void) {
        int check, n, action;
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

	check = scanf("%d", &action);
	if (check == 0) {
                printf("Не указано действие\n");
                return -2;
        }
        if (check == -1) {
                printf("Ошибка данных1\n");
                return -2;
        }
	
	if (action == 1) {
		addition(f, n, str);
	}
	else {
		if (action == -1) {
			subtraction(f, n, str);
		}
		else {
			printf("Ошибка данных\n");
			return -2;
		}
	}

        fclose(f);
}

