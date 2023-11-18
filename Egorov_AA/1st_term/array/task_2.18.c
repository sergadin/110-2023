#include <stdio.h>
#include <stdlib.h>


void coefficients(int deg, int* arr);


void coefficients(int deg, int* arr) {
	for (int n = 0; n <= deg; n++) {
		arr[n] = 1;
		for (int m = n - 1; m > 0; m--) {
			arr[m] += arr[m - 1];
		}
	}
}

int main(void) {
	FILE* input, * output;
	int deg;
	int* arr;
	if ((input = fopen("input.txt", "r")) == NULL) {
		printf("Failed to open input file\n");
		return -1;
	}
	if ((output = fopen("output.txt", "w")) == NULL) {
		printf("Failed to open output file\n");
		fclose(input);
		return -2;
	}
	if (!fscanf(input, "%d", &deg)) {
		printf("Input value error\n");
		return -3;
	}
	arr = (int*)malloc((deg + 1) * sizeof(int));
	if (arr == NULL) {
		printf("Memory allocation error\n");
		return -4;
	}
	coefficients(deg, arr);
	for (int i = 0; i <= deg; i++) {
		fprintf(output, "%d  ", arr[i]);
	}
	fclose(input);
	fclose(output);
	free(arr);
	return 0;
}
