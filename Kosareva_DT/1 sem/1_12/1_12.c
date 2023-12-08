#include <stdio.h>

int first_maximum(FILE *f);
int first_maximum(FILE *f) {
	int position_max, position_now, max, new_digit, check;
	
	check = fscanf(f, "%d", &new_digit);
	if (check != 1) {
		printf("Ошибка данных\n");
		return -2;
	}

	max = new_digit;
	position_max = 1;
    position_now = 1;

	while ((check = fscanf(f, "%d", &new_digit)) && check == 1) {
        position_now += 1;
		if (new_digit > max) {
			max = new_digit;
			position_max = position_now;
		}
	}
	if (check == 0) {
        printf ("Ошибка данных\n");
        return -2;
    }
	
	printf("%d\n", position_max);
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
	first_maximum(f);
    fclose(f);
    return 0;
}

