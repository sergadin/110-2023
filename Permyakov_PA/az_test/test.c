#include <stdio.h>
#include <stdlib.h>

int good_nums_from_A(int length1, double* arrA, int length2, double* arrB);

int main(void)
{
	FILE* inputA;
	FILE* inputB;
	FILE* output;
	int length1 = 0;
	int length2 = 0;
	double* arrA;
	double* arrB;
        int counter = 0;
        output = fopen("output.txt", "w");
        if (output == NULL){
                return -1;
        }
	inputA = fopen("inA.txt", "r");
	if (inputA == NULL){
		printf("incorrect input file A");
		fclose(inputA);
		fclose(output);
		return -1;
	}
	inputB = fopen("inB.txt", "r");
	if (inputB == NULL){
                printf("incorrect input file B");
		fclose(inputA);
		fclose(inputB);
		fclose(output);
                return -1;
        }
	inputB = fopen("inB.txt", "r");
	if (!fscanf(inputA, "%d", &length1) || (length1 < 1)){
		fclose(inputA);
                fclose(inputB);
                fclose(output);
		return -1;
	}
	if (!fscanf(inputB, "%d", &length2) || (length2 < 1)){
		fclose(inputA);
                fclose(inputB);
                fclose(output);
                return -1;
        }
	arrA = (double*)malloc((length1) * sizeof(double));
	arrB = (double*)malloc((length2) * sizeof(double));
	if ((arrA == NULL) || (arrB == NULL)){
		printf("Memory allocation error\n");
		fclose(inputA);
                fclose(inputB);
                fclose(output);
		return -1;
	}
	for (int i = 0; i < length1; i++){
		if(!fscanf(inputA, "%lf", &arrA[i])){
			fclose(inputA);
                	fclose(inputB);
                	fclose(output);
			return -1;
		}
	}
	for (int i = 0; i < length2; i++){
                if(!fscanf(inputB, "%lf", &arrB[i])){
                        fclose(inputA);
                	fclose(inputB);
                	fclose(output);
			return -1;
                }
        }
	counter = good_nums_from_A(length1, arrA, length2, arrB);
	fprintf(output, "%d", counter);
	for (int i = 0; i < counter; i++){
		fprintf(output, "%lf", arrA[i]);
	}
	fclose(inputA);
        fclose(inputB);
        fclose(output);
	free(arrA);
	free(arrB);
	return 0;
}

int good_nums_from_A(int length1, double* arrA, int length2, double* arrB)
{
	int counter = 0;
	double sum = 0;
	for (int i = 0; i < length1; i++){
		if (i < length2){
			sum += arrB[i];
		}
		if (sum < arrA[i]){
			arrA[counter] = arrA[i];
			counter++;
		}
	}
	return counter;
}
