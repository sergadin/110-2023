#include <stdlib.h>
#include <stdio.h>
#include "matrix_6.h"

struct Test{
	char *name;
	int n;
};

int main(void) {
	FILE *f = NULL;
	double **matrix = NULL;
	double *v = NULL;
	double eps = 0.000001;
	int n;
	struct Test entry[5] = {
		{"a1.txt", 3},
		{"a2.txt", 5},
		{"a3.txt", 3},
		{"a4.txt", 2},
		{"a5.txt", 4}
	};
	
	for (int i=0; i<5; i++) {
		printf("%d: ", i+1);
		f = fopen(entry[i].name, "r");
		if (f == NULL) {
			printf("Файл не открылся\n");
			break;
		}
		n = entry[i].n;
		
		v = (double *)malloc(n * sizeof(double));
		if (v == NULL) {
			printf("Ошибка памяти\n");
			fclose(f);
			break;
		}
		
		matrix = (double **)malloc(n * sizeof(double *));
		if (matrix == NULL) {
			printf("Ошибка памяти\n");
			fclose(f);
			free(v);
			break;
		}
		
		for (int j=0; j<n; j++) {
			matrix[j] = (double *)malloc((n+1) * sizeof(double));
			if (matrix[j] == NULL) {
				printf("Ошибка памяти\n");
				goto error;
			}
			
			for (int k=0; k<(n+1); k++) {
				if (fscanf(f, "%lf", &matrix[j][k]) != 1) {
					printf("Ошибка данных\n");
					goto error;
				}
			}
		}
		
		if (solve(matrix, n, eps, v) == 0) {
			for (int j=0; j<n; j++) {
				printf("%lf ", v[j]);
			}
			printf("\n");
		}
		else {
			printf("Решение не найдено\n");
		}
		
		fclose(f);
		free(v);
		for (int j=0; j<n; j++) {
			free(matrix[j]);
		}
		free(matrix);
		
		continue;
		
		error :
			fclose(f);
			free(v);
			for (int j=0; j<n; j++) {
				free(matrix[j]);
			}
			free(matrix);
	}
	return 0;
}
