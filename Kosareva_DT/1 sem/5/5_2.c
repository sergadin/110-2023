#include <stdio.h>
#include <stdlib.h>

int convex(int *dots, int n);
int sgn_area(int x1, int y1, int x2, int y2, int x3, int y3);
int main(void);

int sgn_area(int x1, int y1, int x2, int y2, int x3, int y3) {
	int a, b, c, d;
	
	a = x2 - x1;
	b = y2 - y1;
	c = x3 - x1;
	d = y3 - y1;
	
	if  ((a*d - b*c) > 0) {
		return 1;
	}
	return -1;
}

int convex(int *dots, int n) {
	int count, i;
	count = 0;
	for (i=0; i<n; i+=2) {
		count += sgn_area(dots[i], dots[i+1], dots[(i+2)%n], dots[(i+3)%n], dots[(i+4)%n], dots[(i+5)%n]);
	}
	if (count < 0) {
		count = 0-count;
	}
	if (count*2 == n) {
		printf("Выпуклый\n");
		return 0;
	}
	printf("Невыпуклый\n");
	return 0;
}

int main(void) {
	int n, check, i;
	int *dots = NULL;
	FILE *f;
	
	printf("Сколько точек?\n");
	check = scanf("%d", &n);
	if (check != 1) {
		printf("Ошибка\n");
		return -1;
	}
	if (n < 3) {
		printf("Мало точек...\n");
		return -1;
	}
	
	f = fopen("in.txt", "r");
	if (f == NULL) {
		printf("Ошибка\n");
		return -1;
	}
	
	n = 2*n;
	dots = (int *)malloc(n*sizeof(int));
	
	for(i=0; i<n; i++) {
		check = fscanf(f, "%d", &dots[i]);
		if (check != 1) {
			printf("Ошибка\n");
			fclose(f);
			return -1;
		}
	}
	fclose(f);
	
	convex(dots, n);
	
	return 0;
}
