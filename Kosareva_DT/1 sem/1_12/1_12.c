#include <stdio.h>

int first_maximum(FILE *f);
int first_maximum(FILE *f) {
	int number, now, max, new_digit, check;
	
	check = fscanf(f, "%d", &new_digit);
	if (check != 1) {
		printf("Ошибка данных\n");
		return -2;
	}

	max = new_digit;
	number = 1;
	now = 2;

	check = fscanf(f, "%d", &new_digit);
        if (check == 0) {
                printf("Ошибка данных\n");
                return -2;
        }

	while (check == 1) {
		if (new_digit > max) {
			max = new_digit;
			number = now;
		}

		check = fscanf(f, "%d", &new_digit);
        	if (check == 0) {
                	printf("Ошибка данных\n");
        	        return -2;
	        }
		now++;
	}
	
	printf("%d\n", number);
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
	return first_maximum(f);
}

