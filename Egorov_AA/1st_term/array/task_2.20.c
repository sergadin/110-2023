#include <stdio.h>
#include <stdlib.h>


void united_set(int* arr_a, int* arr_b, int* arr_c,
	int len_a, int len_b);


void united_set(int* arr_a, int* arr_b, int* arr_c,
	int len_a, int len_b) {
	int a = 0, b = 0, c = 0;
	while ((a < len_a) && (b < len_b)) {
		if (a < b) {
			arr_c[c] = arr_a[a];
			c++;
			a++;
		}
		else {
			arr_c[c] = arr_b[b];
			c++;
			b++;
		}
	}
	while (a < len_a) {
		arr_c[c] = arr_a[a];
		c++;
		a++;
	}
	while (b < len_b) {
		arr_c[c] = arr_b[b];
		c++;
		b++;
	}
}

int main(void) {
	FILE* input_1, * input_2, * output;
	int* arr_a, * arr_b, * arr_c;
	int len_a, len_b, code;

	if ((input_1 = fopen("input_1.txt", "r")) == NULL) {
		printf("Failed to open first input file\n");
		code = -1;
		goto stop_7;
	}
	if ((input_2 = fopen("input_2.txt", "r")) == NULL) {
		printf("Failed to open second input file\n");
		code = -2;
		goto stop_6;
	}
	if ((output = fopen("output.txt", "w")) == NULL) {
		printf("Failed to open output file\n");
		code = -3;
		goto stop_5;
	}

	if (!fscanf(input_1, "%d", &len_a)) {
		printf("first input value error\n");
		code = -4;
		goto stop_4;
	}
	if (!fscanf(input_2, "%d", &len_b)) {
		printf("second input value error\n");
		code = -5;
		goto stop_4;
	}

	arr_a = (int*)malloc((len_a + 1) * sizeof(int));
	arr_b = (int*)malloc((len_b + 1) * sizeof(int));
	arr_c = (int*)malloc((len_a + len_b) * sizeof(int));

	if (arr_a == NULL) {
		printf("Memory allocation error\n");
		code = -6;
		goto stop_4;
	}
	if (arr_b == NULL) {
		printf("Memory allocation error\n");
		code = -7;
		goto stop_3;
	}
	if (arr_c == NULL) {
		printf("Memory allocation error\n");
		code = -8;
		goto stop_2;
	}

	for (int i = 0; i < len_a; i++) {
		if ((fscanf(input_1, "%d", &arr_a[i])) != 1) {
			printf("input value error\n");
			code = -9;
			goto stop_1;
		}
	}
	for (int i = 0; i < len_b; i++) {
		if ((fscanf(input_2, "%d", &arr_b[i])) != 1) {
			printf("input value error\n");
			code = -10;
			goto stop_1;
		}
	}

	united_set(arr_a, arr_b, arr_c, len_a, len_b);

	for (int i = 0; i < (len_a + len_b); i++) {
		fprintf(output, "%d ", arr_c[i]);
	}

	code = 0;
	stop_1:
	free(arr_c);
	stop_2:
	free(arr_b);
	stop_3:
	free(arr_a);
	stop_4:
	fclose(output);
	stop_5:
	fclose(input_2);
	stop_6:
	fclose(input_1);
	stop_7:
	return code;
}
