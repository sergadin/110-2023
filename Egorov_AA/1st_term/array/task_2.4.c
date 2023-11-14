#include <stdio.h>
#include <stdlib.h>


void comparasion(int* arr_a, int* arr_b, int len_a, int len_b);


void comparasion(int* arr_a, int* arr_b, int len_a, int len_b) {
	int count = 0;
	for (int i = 0; i <= len_a; i++) {
		for (int j = 0; j <= len_b; j++) {
			if (arr_a[i] == arr_b[j]) {
				count++;
				break;
			}
		}
	}
	if (count == len_a) {
		if (len_a == len_b) {
			printf("A equals B\n");
		}
		else {
			printf("A does not equal B\n");
		}
		printf("A is a subset of B\n");
	}
	else {
		printf("A does not equal B\nA is not a subset of B\n");
	}
}

int main(void) {
	FILE* input_1, * input_2;
	int* arr_a, * arr_b;
	int len_a, len_b;
	if ((input_1 = fopen("input_1.txt", "r")) == NULL) {
		printf("Failed to open first input file\n");
		fclose(input_1);
		return -1;
	}
	if ((input_2 = fopen("input_2.txt", "r")) == NULL) {
		printf("Failed to open second input file\n");
		fclose(input_1);
		fclose(input_2);
		return -2;
	}
	if (!fscanf(input_1, "%d", &len_a)) {
		printf("first input value error\n");
		fclose(input_1);
		fclose(input_2);
		return -3;
	}
	if (!fscanf(input_2, "%d", &len_b)) {
		printf("second input value error\n");
		fclose(input_1);
		fclose(input_2);
		return -4;
	}
	arr_a = (int*)malloc(len_a * sizeof(int));
	arr_b = (int*)malloc(len_b * sizeof(int));
	if (arr_a == NULL) {
		printf("Memory allocation error\n");
		fclose(input_1);
		fclose(input_2);
		return -5;
	}
	if (arr_b == NULL) {
		printf("Memory allocation error\n");
		fclose(input_1);
		fclose(input_2);
		return -6;
	}
	for (int i = 0; i < len_a; i++) {
		fscanf(input_1, "%d", &arr_a[i]);
	}
	for (int i = 0; i < len_b; i++) {
		fscanf(input_2, "%d", &arr_b[i]);
	}
	comparasion(arr_a, arr_b, len_a, len_b);
	free(arr_a);
	free(arr_b);
	fclose(input_1);
	fclose(input_2);
	return 0;
}
