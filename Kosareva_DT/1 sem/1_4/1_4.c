#include <stdio.h>

int how_much(FILE *f);
int how_much(FILE *f) {
    int count, last, new, check;
	count = 0;

	check = fscanf(f, "%d", &last);
	if (check == 0) {
		printf("Ошибка данных\n");
		return -2;
	}
	if (check == -1) {
		printf("%d\n", count);
		return 0;
	}
	check = fscanf(f, "%d", &new);
        if (check == 0) {
                printf("Ошибка данных\n");
                return -2;
        }
	while (check == 1) {
		if (new > last) count++;
		last = new;
		check = fscanf(f, "%d", &new);
        	if (check == 0) {
                	printf("Ошибка данных\n");
                	return -2;
        	}
	}
	printf("%d\n", count);
	fclose(f);
	return 0;
}
int main(void) {
	char str[60];
	FILE *f;
	printf("Введите имя файла или указатель на него: ");
	scanf("%60s", str);
	f = fopen(str, "r");
	if (f == NULL) {
		printf("Не удалось открыть файл\n");
		return -1;
	}
	how_much(f);
    return 0;
}
