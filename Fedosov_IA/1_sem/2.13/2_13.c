#include <stdio.h>
#include <stdlib.h>


void get_half_sum(double * array, int len);
//функция заменяет все элементы на полусумму соседних элементов

int main(void){
	int len;
	double* array = NULL;
	FILE *fin, *fout;
	int i;
	
	fin = fopen("input.txt", "r");
	if (fin == NULL){
		printf("не удалось открыть файл 'input.txt'\n");
		fclose(fin);
		return -1;
	}

	fout = fopen("output.txt", "w");
        if (fout == NULL){
                printf("не удалось открыть файл 'output.txt'\n");
		fclose(fin);
		fclose(fout);
		return -1;
        }

	if (fscanf(fin, "%d", &len) != 1){
		printf("ошибка входных данных\n");
		fclose(fin);
        fclose(fout);
		return -1;
	}

	array = (double *)malloc(len * sizeof(double));

	for (i = 0; i < len; i++){
		if (fscanf(fin, "%lf", &array[i]) != 1){
			printf("неверные входные данные для массива\n");
			fclose(fin);
            fclose(fout);
			free(array);
			return -1;
		}
	}
	
	if (len <= 2){
		printf("массив равен исходному тк в нем менее 3-х элементов\n");
		fclose(fin);
        fclose(fout);
		return -1;
	}

	get_half_sum(array, len);

	for(i = 0; i < len; i++){
		fprintf(fout, "%lf ", array[i]);
	}

	fclose(fin);
	fclose(fout);
	free(array);
	
	return 0;
}


void get_half_sum(double * array, int len){
	double prev_value, original_value = array[0];

	for(int i = 1; i < len - 1; i++){
		prev_value = original_value;
		original_value = array[i];
		array[i] = (prev_value + array[i + 1]) / 2;
	}
}










