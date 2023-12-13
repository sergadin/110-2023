#include <stdio.h>

int length(FILE *f);
int length(FILE *f) {
	int max[2], new[2], next, check;
	
	check = fscanf(f, "%d", &new[0]);
	if (check == 0) {
		printf("Ошибка данных\n");
		return -2;
	}
	
	max[0] = new[0];
	max[1] = 1;
	new[1] = 1;
	while ((check = fscanf(f, "%d", &next)) && (check == 1)) {
		if (next == new[0]) {
			if (new[0] > 0) {
				new[1]++;
			}
		}
		else {
			if (new[0]*new[1] > max[0]*max[1]) {
				max[0] = new[0];
				max[1] = new[1];
			}
			new[1] = 1;
			new[0] = next;
		}
	}
	if (new[0]*new[1] > max[0]*max[1]) {
            max[0] = new[0];
            max[1] = new[1];
        }
	if (check == 0) {
        printf("Ошибка данных\n");
        return -2;
    	}
	printf("%d\n", max[1]);
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
