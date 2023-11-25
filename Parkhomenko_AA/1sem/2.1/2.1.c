//Симметричны ли значения элементов массива целых чисел?
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int symmetric_massiv(int *Array, int len);
//функция определяет симметричность элементов массива

int symmetric_massiv(int *Array, int len){

	int centre = len/2;
	int i, j;

 	for (i = 0, j = len-1; i < centre && j > centre; i++, j--) {
        if (Array[i] != Array[j]) {
            return 0;
        }
    }
  
    return 1;
}


int main(void) {
	FILE *file_in = fopen("2.1.1.txt", "r");
	FILE *file_out = fopen("2.1.2.txt", "w");
	int len = 0, main_return_code = 0;
	int *Array = NULL;
    
	if (file_in == NULL) {
		printf("error opening the file_in\n");
		return -1;
	}
	
    if (file_out == NULL) {
		printf("error opening the file_out\n");
        fclose(file_in);
		return -1;
	}
	
	if (fscanf(file_in, "%d", &len) != 1) {
		printf("пустой файл\n");
        fclose(file_in);
        fclose(file_out);
		return -1;
	}
	
       Array = (int *)malloc(len*sizeof(int)); // В массив записываются значения из введенного файла.
	if (Array == NULL){
		printf("Оперативная память не выделена\n");
		main_return_code = -1;
		goto terminate;
	}

	
	for (int i=0; i < len; ++i){
		if (fscanf(file_in, "%d", &Array[i])!=1){
			printf("В файле недостаточкно значений\n");
			main_return_code = -1;
			goto terminate_1;
		}
	}
	symmetric_massiv(Array, len);

	for (int i = 0; i < len; i++) {
		fprintf(file_out, "%d ", Array[i]);
	}
	
	if (symmetric_massiv(Array, len)) {
		printf("Массив симметричен\n");
	}
    else {
    printf("Массив не симметричен\n");
    }
    terminate_1:
	free(Array);
    terminate:
	fclose(file_in);
	fclose(file_out);
	
	return main_return_code;
}
