#include <stdio.h>
#include <stdlib.h>


int comparasion(int* arr_a, int* arr_b, int len_a, int len_b);


int comparasion(int* arr_a, int* arr_b, int len_a, int len_b) {
	int count = 0;
	for (int i = 0; i < len_a; i++) {
		for (int j = 0; j < len_b; j++) {
			if (arr_a[i] == arr_b[j]) {
				count++;
				break;
			}
		}
	}
	if (count == len_a) {
		if (len_a == len_b) {
			return 1;
		}
		else {
			return 2;
		}
	}
	else {
		return 3;
	}
}


int main(void) {

	FILE* input_1, * input_2, * output;
	int* arr_a, * arr_b;
	int len_a, len_b, code, res;

	if ((input_1 = fopen("input_1.txt", "r")) == NULL) {
		printf("Failed to open first input file\n");
		code = -1;
		goto stop_6;
	}
	if ((input_2 = fopen("input_2.txt", "r")) == NULL) {
		printf("Failed to open second input file\n");
		code = -2;
		goto stop_5;
	}
	if ((output = fopen("output.txt", "w")) == NULL) {
        printf("Failed to open output file\n");
        code = -3;
        goto stop_4;
	}

	if (!fscanf(input_1, "%d", &len_a)) {
		printf("input value error\n");
		code = -4;
		goto stop_3;
	}
	if (!fscanf(input_2, "%d", &len_b)) {
		printf("input value error\n");
		code = -5;
		goto stop_3;
	}

	arr_a = (int*)malloc((len_a + 1) * sizeof(int));
	arr_b = (int*)malloc((len_b + 1) * sizeof(int));

	if (arr_a == NULL) {
		printf("Memory allocation error\n");
		code = -6;
		goto stop_3;
	}
	if (arr_b == NULL) {
		printf("Memory allocation error\n");
		code = -7;
		goto stop_2;
	}

	for (int i = 0; i < len_a; i++) {
		if (!(fscanf(input_1, "%d", &arr_a[i]) == 1)) {
			printf("input value error\n");
			code = -8;
			goto stop_1;
		}
	}
	for (int i = 0; i < len_b; i++) {
		if (!(fscanf(input_2, "%d", &arr_b[i]) == 1)) {
			printf("input value error\n");
			code = -9;
			goto stop_1;
		}
	}

	res = comparasion(arr_a, arr_b, len_a, len_b);

    	if (res == 1) {
		fprintf(output, "A equals B, A is a subset of B");
    	}
    	else if (res == 2) {
        	fprintf(output, "A does not equal B, A is a subset of B");
    	}
    	else if (res == 3) {
        	fprintf(output, "A does not equal B, A is not a subset of B");
    	}

	code = 0;
	stop_1:
	free(arr_b);
	stop_2:
	free(arr_a);
	stop_3:
	fclose(output);
	stop_4:
	fclose(input_2);
	stop_5:
	fclose(input_1);
    	stop_6:
	return code;
}
