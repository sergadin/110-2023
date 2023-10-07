#include <stdio.h>

int how_much(FILE *f);
int how_much(FILE *f) {
    int count, last, new;
	count = 0;
	fscanf(f, "%d", &last);
	while (fscanf(f, "%d", &new) == 1) {
		if (new > last) count++;
		last = new;
	}
	printf("%d\n", count);
	fclose(f);
	return 0;
}
int main(void) {
	char str[30];
	FILE *f;
	printf("Введите имя файла или указатель на него: ");
	scanf("%30s", str);
	f = fopen(str, "r");
	if (f == NULL) {
		printf("Не удалось открыть файл\n");
		return -1;
	}
	how_much(f);
    return 0;
}
