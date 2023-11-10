#include <stdio.h>
#include <stdlib.h>


void coefficients(int deg);


void coefficients(int deg) {
	int* arr = (int*)malloc((deg + 1) * sizeof(int));
	for (int n = 0; n <= deg; n++) {
		arr[n] = 1;
		for (int m = n - 1; m > 0; m--) {
			arr[m] += arr[m - 1];
		}
	}
	for (int i = 0; i <= deg; i++) {
		printf("%d  ", arr[i]);
	}
	free(arr);
}


int main(void) {
	FILE* input;
	int deg;
	if ((input = fopen("input.txt", "r")) == NULL) {
		printf("Failed to open file\n");
		return -1;
	}
	if (fscanf(input, "%d", &deg)) {
		coefficients(deg);
	}
	else
		printf("Input value error\n");
	return 0;
}
