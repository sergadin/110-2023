#include <stdio.h>

int length(FILE *f);
int length(FILE *f) {
	int max_length, new_length, max_sum, new_sum, prev, new, check;
	max_length = 0;
	new_length = 0;
	max_sum = 0;
	new_sum = 0;
	prev = 0;
	check = fscanf(f, "%d", &new);
	if (check == 0) {
		printf("Ошибка данных\n");
		return -2;
	}
	while (check == 1) {
		if (new == prev) {
			new_length++;
			new_sum += new;
		}
		else {
			if (new_sum > max_sum) {
				max_sum = new_sum;
				max_length = new_length;
			}
			new_length = 1;
			new_sum = new;
			prev = new;
		}
		check = fscanf(f, "%d", &new);
		if (check == 0) {
                	printf("Ошибка данных\n");
                	return -2;
		}
	}
	printf("%d\n", max_length);
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
        length(f);
    return 0;
}
