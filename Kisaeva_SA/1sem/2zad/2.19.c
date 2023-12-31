//2.19 Элементы массива не убывают. Двоичным поиском определить позицию, где в этот массив можно вставить данное число x.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int bi_search(double *mas, int len, double x);
// Определяет позицию (itog_pos) в массиве для числа x, чтобы массив оставался неубывающим


int bi_search(double *mas, int len, double x) {
	int lev = 0;      // левая грацица
	int prav = len - 1;  // правая граница
	int mid; // середина отрезка
	int itog_pos = -1;
	
	if (len == 0) {
		printf("error, net massiva, len = 0 \n");
		itog_pos = 0;
		return itog_pos;
	}
	
	if (x < mas[0]) {
		itog_pos = 0;
		return itog_pos;
	}
	else if (x > mas[len - 1]) {
		itog_pos = len;
		return itog_pos;
	}

	while (lev <= prav) {
		mid = (lev + prav) / 2;
		if ((x > mas[mid]) && (x < mas[mid + 1])){
			itog_pos = mid + 1;
			break;
		}
		if (mas[mid] > x) {
			prav = mid - 1;
		} 
		if (mas[mid] < x) {
			lev = mid + 1;
		} 
		else {
			itog_pos = mid;
			break;
		}
	}
	
	return itog_pos;
}


int main(void) {
	int len; //длина массива
	int position;
	double x;
	double* mas = NULL;
	FILE *file_in = fopen("input.txt", "r");
	FILE *file_out = fopen("output.txt", "w");
    
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
		printf("error, v faile pusto / ne tot tip y dlinu\n");
		fclose(file_in);
		fclose(file_out);
		return -1;
	}
	
	mas = (double*) malloc((len)*sizeof(double));
	
	if (mas == NULL) {
		printf("Memory error\n");
		fclose(file_in);
		fclose(file_out);
		return -1;
	}
	
	for (int i = 0; i < len; i ++) {
		if (fscanf(file_in, "%lf", &mas[i]) != 1) {
			printf("error, problema s tipom elementov massiva / dlina massiva < len\n");
			free(mas);
			fclose(file_in);
			fclose(file_out);
			return -1;
		}
	}
	
	for (int i = 0; i < (len - 1); i ++) {
		if (mas[i + 1] < mas[i]) {
			printf("error, massiv ne ne ybuvaet\n");
			free(mas);
			fclose(file_in);
			fclose(file_out);
			return -1;
		}
	}
	
	printf("vvedite chislo X \n");
	scanf("%lf", &x);
	
	position = bi_search(mas, len, x);
	fprintf(file_out, "position  %d\n", position);
	
	if (len != 0) {
		printf("rezultat napechatan \n");	
	}
	
	free(mas);
	fclose(file_in);
	fclose(file_out);
	return 0;
}