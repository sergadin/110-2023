#include <stdlib.h>
#include <stdio.h>
#include "matrix_1.h"

struct Test{
	char *name;
	int n;
	int m;
};

int main(void) {
	FILE *f = NULL;
	double *matrix = NULL;
	int i, j, n, m;
	struct Test entry[5] = {
		{"a1.txt", 3, 4},
		{"a2.txt", 5, 5},
		{"a3.txt", 9, 10},
		{"a4.txt", 1, 10},
		{"a5.txt", 4, 3}
	};
	
	for (i=0; i<5; i++) {
		printf("%d: ", i+1);
		f = fopen(entry[i].name, "r");
		if (f == NULL) {
			printf("Файл не открылся\n");
			goto error;
		}
		n = entry[i].n;
		m = entry[i].m;
		matrix = (double *)malloc(n*m*sizeof(double));
		for (j=0; j<n*m; j++) {
			if (fscanf(f, "%lf", &matrix[j]) != 1) {
				printf("Ошибка чтения\n");
				fclose(f);
				free(matrix);
				goto error;
			}
		}
		rank(matrix, n, m, 0.00000001);
		error :
	}
	return 0;
}
