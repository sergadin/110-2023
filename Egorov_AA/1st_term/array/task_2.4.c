#include <stdio.h>
#include <stdlib.h>


int comparasion(int* arr_1, int* arr_2, int* error);


int comparasion(int* arr_1, int* arr_2, int* error) {
    
}

int main(void) {
	FILE* input_1, * input_2;
	int* arr_1, * arr_2;
	int len_1, len_2, error;
	if ((input_1 = fopen("input_1.txt", "r")) == NULL) {
		printf("Failed to open first input file\n");
		return -1;
	}
	if ((input_2 = fopen("input_2.txt", "r")) == NULL) {
		printf("Failed to open second input file\n");
		return -2;
	}
	if (!fscanf(input_1, "%d", &len_1)) {
		printf("first input value error\n");
		return -3;
	}
	if (!fscanf(input_2, "%d", &len_2)) {
		printf("second input value error\n");
		return -4;
	}
	arr_1 = (int*)malloc(len_1 * sizeof(int));
	arr_2 = (int*)malloc(len_2 * sizeof(int));
	if (arr_1 == NULL) {
		printf("Memory allocation error");
		return -5;
	}
	if (arr_2 == NULL) {
		printf("Memory allocation error");
		return -6;
	}
	for (int i = 0; i < len_1; i++) {
        fscanf(input_1, "%d", &arr_1[i]);
    }
	for (int i = 0; i < len_2; i++) {
        fscanf(input_2, "%d", &arr_2[i]);
    }
	comparasion(arr_1, arr_2, &error);
    for (int i = 0; i < len_1; i++) {
        printf("%d", arr_1[i]);
    }
    for (int i = 0; i < len_2; i++) {
        printf("%d", arr_2[i]);
    }
    return 0;
}
