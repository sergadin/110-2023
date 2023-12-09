#include <stdio.h>

int countSetBits(int num);
void printSubsets(FILE* output, int n, int k);


int countSetBits(int num) {
	int count = 0;
	while (num) {
		count += num & 1;
		num >>= 1;
	}
	return count;
}


void printSubsets(FILE* output, int n, int k) {
	for (int i = 0; i < (1 << n); i++) {
		if (countSetBits(i) == k) {
			fprintf(output, "{ ");
			for (int j = 0; j < n; j++) {
				if (i & (1 << j))
					fprintf(output, "%d ", j + 1);
			}
			fprintf(output, "}\n");
		}
	}
}


int main(void) {
	FILE* output;
	int n, k;
	if ((output = fopen("output.txt", "w")) == NULL)
		printf("failed to open output file");

	printf("enter the length of a set {1, 2, ... , N}: ");
	scanf("%d", &n);
	printf("enter the length of a subset (k): ");
	scanf("%d", &k);

	printSubsets(output, n, k);

	return 0;
}
