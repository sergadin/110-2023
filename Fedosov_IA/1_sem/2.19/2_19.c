#include <stdio.h>
#include <stdlib.h>


int find_position(int *array, int len, int value);


int main(void){
	int *array = NULL;
	int len, value, res;
	FILE *fin, *fout;

	scanf("%d", &value);

	fin = fopen("input.txt", "r");
	if (fin == NULL){
		printf("не удалось открыть файл 'input.txt'\n");
		return -1;
	}

	fout = fopen("output.txt", "w");
    if (fout == NULL){
        printf("не удалось открыть файл 'output.txt'\n");
        fclose(fin);
        return -1;
    }

	if (fscanf(fin, "%d", &len) != 1){
		printf("ошибка входных данных");
        fclose(fin);
        fclose(fout);
		return -1;
	}

	array = (int *)malloc(len * sizeof(int));

	for (int i = 0; i < len; i++){
		if (fscanf(fin, "%d", &array[i]) != 1){
			printf("неверные входные данные для массива\n");
			fclose(fin);
            fclose(fout);
			free(array);
			return -1;
		}
	}

	res = find_position(array, len, value);

	if (res >= 0){
		printf("%d\n", res);
        fprintf(fout, "%d", res);
	}
	
	free(array);
	fclose(fin);
	fclose(fout);
	return 0;
}

	
/*
int find_position(int *array, int len, int value){
	int n = len;

	if (len <= 0){
		printf("массив пуст или неверное значение длинны");
		return -1;
	}

	if (len == 1){
		if (value > array[0]){
			return 1;
		} else {
			return 0;
		}
	}

	while (1){

		if (array[len / 2] < value){
			if (len / 2 == n){
				return n;
			}
			len += len / 2;
		} else {
			if (len / 2 == 0){
				return 0;
			}
			len -= len / 2;
		}

		if (array[len / 2] <= value && array[len / 2 + 1] >= value){
			return (len / 2 + 1);
		}
	}
}
*/


int find_position(int *array, int len, int value){
	int left_border = 0;     
	int right_border = len - 1;  
	int midpoint; 
	int position = -1;
	
	if (len <= 0) {
		printf("неверные входные данные \n");
		return -1;
	}
	
	if (value < array[0]) {
		return 0;
	} else if (value > array[len - 1]) {
		return len;
	}

	while (left_border <= right_border) {
		midpoint = (left_border + right_border) / 2;

		if ((value > array[midpoint]) && (value < array[midpoint + 1])){
			position = midpoint + 1;
			break;
		}

		if (array[midpoint] > value) {
			right_border = midpoint - 1;
		} else if (array[midpoint] < value) {
			left_border = midpoint + 1;
		} else {
			position = midpoint;
			break;
		}
	}
	
	return position;
}










